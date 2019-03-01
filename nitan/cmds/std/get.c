// Filename : /cmds/verb/get.c

#include <ansi.h>
#include <command.h>
#include <config.h>

inherit F_CLEAN_UP;

int do_get(object me, object ob, int raw);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string from, item;
        object obj, *inv, env, obj2;
        mixed info;
        string msg;
        int i, amount;

        if (! arg) return notify_fail("你要撿起什麼東西？\n");

        // Check if a container is specified.
        if (sscanf(arg, "%s from %s", arg, from) == 2)
        {
                env = present(from, me);
                if (! env) env = present(from, environment(me));
                if (! env) return notify_fail("你找不到 " + from + " 這樣東西。\n");
                if (me == env) return notify_fail("毛病！你要搜自己的身？\n");
                if( query("no_get_from", env) || living(env) )
                {
                        if (! wizardp(me))
                                return notify_fail("你不能搜身。\n");

                        if (wiz_level(me) <= wiz_level(env) &&
                            ! MASTER_OB->valid_write(base_name(env), me, "get"))
                                return notify_fail("你的巫師等級必須比對方高才能搜身。\n");

                        if (wiz_level(me) < 3)
                                return notify_fail("你的巫師等級不夠搜身。\n");

                        if (! me->is_admin())
                        {
                                switch (SECURITY_D->query_site_privilege("get"))
                                {
                                case "all":
                                        break;

                                case "noneuser":
                                        if (playerp(env))
                                                return notify_fail("你不能搜玩家控制人物的身。\n");

                                case "user":
                                        if (! playerp(env))
                                                return notify_fail("你不能搜非玩家控制人物的身。\n");

                                default:
                                        return notify_fail("你不能搜身。\n");
                                }
                        }
                }
        } else env = environment(me);

        // Check if a certain amount is specified.
        if (sscanf(arg, "%d %s", amount, item) == 2)
        {
                if (! objectp(obj = present(item, env)) && item[0] > 160)
                {
                        inv = all_inventory(env);
                        for (i = 0; i < sizeof(inv); i++)
                        if (filter_color(inv[i]->name(1)) == item)
                        {
                                obj = inv[i];
                                break;
                        }
                }

                if (! objectp(obj))
                        return notify_fail("這裡沒有這樣東西。\n");

                if (! obj->query_amount())
                        return notify_fail( obj->name() + "不能被分開拿走。\n");

                if (amount < 1)
                        return notify_fail("東西的個數至少是一個。\n");

                if (amount > obj->query_amount())
                        return notify_fail("這裡沒有那麼多的" + obj->name() + "。\n");

                else if (amount == (int)obj->query_amount())
                {
                        // get object when fighting costs time
                        if (me->is_fighting() && ! me->is_busy()) me->start_busy(1);
                        return do_get(me, obj, 0);
                } else
                {
                        obj2 = new(base_name(obj));
                        if (! objectp(obj2)) 
                                return 0;
                        obj->set_amount((int)obj->query_amount() - amount);
                        obj2->set_amount(amount);
                        // Counting precise amount costs more time.
                        if (me->is_fighting() && ! me->is_busy()) me->start_busy(3);
                        if (! do_get(me, obj2, 0))
                        {
                                obj2->move(env);
                                return 0;
                        }
                        if (environment(obj)->no_limit_amount())
                                environment(obj)->save();
                        return 1;
                }
        }

        // Check if we are makeing a quick get.
        if (arg == "all")
        {
                object my_env;

                if (me->is_fighting())
                        return notify_fail("你還在戰鬥中！只能一次拿一樣。\n");

                if (! env->query_max_encumbrance())
                        return notify_fail("那不是容器。\n");

                my_env = environment(me);
                inv = all_inventory(env);
                for (i = 0, amount = 0; i < sizeof(inv); i++)
                {
                        if (! living(me)) break;
                        if (environment(me) != my_env) break;
                        if( inv[i]->is_character() || query("no_get", inv[i]) )
                                continue;
                        amount += do_get(me, inv[i], 1);
                }
                if (! amount)
                {
                        write("你什麼都沒有揀起來。\n");
                        return 1;
                }

                if (env->is_character())
                        msg = me->name() + "從" + env->name() + "身上搜出了一堆東西。\n";
                else
                if (env == my_env)
                        msg = me->name() + "把地上的東西都揀了起來。\n";
                else
                        msg = me->name() + "把" + env->name() + "裡面的東西都拿了出來。\n";
                message("vision", msg, environment(me), ({ me }));
                write("撿好了。\n");
                return 1;
        }

        if (! objectp(obj = present(arg, env)) && arg[0] > 160)
        {
                inv = all_inventory(env);
                for (i = 0; i < sizeof(inv); i++)
                if (filter_color(inv[i]->name(1)) == arg)
                {
                        obj = inv[i];
                        break;
                }
        }
                
        if (! objectp(obj) || living(obj))
                return notify_fail("你附近沒有這樣東西。\n");

        if( query("no_uget", obj) && playerp(env) )
                return notify_fail("這個東西拿不起來。\n");

        if( info=query("no_get", obj) )
                if( functionp(info) ) 
                        info = evaluate(query("no_get", obj));

        if( info )
                return notify_fail(stringp(info) ? info : "這個東西拿不起來。\n");

        // get object when fighting costs time
        if (me->is_fighting() && ! me->is_busy()) me->start_busy(1);

        return do_get(me, obj, 0);
}
        
int do_get(object me, object obj, int raw)
{
        object old_env, *guard;
        string msg;
        int equipped;
        object *obs;

        if (! obj) return 0;
        old_env = environment(obj);

        if (obj->is_character() && living(obj)) return 0;
        if( query("no_get", obj))return 0;

        if( guard=query_temp("guarded", obj) )
        {
                guard = filter_array(guard, (: objectp($1) && present($1, environment($2)) &&
                                               living($1) && ($1 != $2) :), me);
                if (sizeof(guard))
                        return notify_fail( guard[0]->name() 
                                + "正守在" + obj->name() + "一旁，防止任何人拿走。\n");
        }

        if( time()<query("who_get/time", obj) && 
            query("id", me) != query("who_get/id", obj) )
                return notify_fail("你還是稍等片刻再撿" + obj->name() + "吧。\n");

        if( query("equipped", obj))equipped=1;
        obs=filter_array(all_inventory(me),(:!query("equipped", $1):));
        if (sizeof(obs) >= MAX_ITEM_CARRIED &&
            ! obj->can_combine_to(me))
                return notify_fail("你身上的東西實在是太多了，沒法再拿東西了。\n");

        if (obj->move(me))
        {
                if (obj->is_character() && obj->query_weight() > 20000)
                {
                        object cloth;
                        int iknow;
                        message_vision("$N將$n扶了起來背在背上。\n", me, obj);
                        cloth=query_temp("armor/cloth", obj);
                        iknow=query("name", me)+"的屍體" == obj->name();
                        if (cloth)
                        {
                                // is the cloth daub with poison ?
                                DAUB_CMD->check_poison(me, cloth, iknow);
                        } else
                        {
                                // is the corpse daub with poison ?
                                DAUB_CMD->check_poison(me, obj, iknow);
                        }
                } else
                {
                        msg = sprintf("$N%s一%s%s。\n",
                                (! old_env || old_env == environment(me)) ? "撿起" :
                                old_env->is_character() ?  "從" + old_env->name() + "身上" + (equipped ? "除下" : "搜出") :
                                old_env->is_tree() ? "從" + old_env->name() +"上摘下" :
                                                     "從" + old_env->name() + "中拿出",
                                query("unit", obj),obj->name());
                        if (! raw)
                                message_vision(msg, me);
                        else
                                write(replace_string(msg, "$N", "你"));
                }
                if (objectp(old_env) && old_env->no_limit_amount())
                        old_env->save();
                return 1;
        }
        else return 0;
}

int help(object me)
{
        write(@HELP
指令格式 : get <物品名稱> | all [from <容器名>]
 
這個指令可以讓你撿起地上或容器內的某樣物品.
 
該命令在可以被授權使用的信息包括：noneuser、user、all。
HELP );
        return 1;
}
