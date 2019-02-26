// get.c
// last updated by April 2001.09.27     禁止在睡房裏拿睡覺人的東西
// last updated by naihe 2002.09.25 
// 各文件可使用set("no_get","信息") 格式自定義no_get信息，
// 使用 set("no_get","1") 格式將使用默認信息：這個東西拿不起來。
// 之前的物件設定為 set("no_get",1) 的，也將使用默認信息。

#include <ansi.h>

inherit F_CLEAN_UP;

int do_get(object me, object ob);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string from, item,no_get_message;
        object obj, *inv, env, obj2;
        int i, amount, newa;

        if( !arg ) return notify_fail("你要撿起什麼東西？\n");
        if( me->is_busy() )
                return notify_fail("你上一個動作還沒有完成！\n");

        // Check if a container is specified.
        if( sscanf(arg, "%s from %s", arg, from)==2 ) {
                env = present(from, me);
                if(!env) env = present(from, environment(me));
                if(!env) return notify_fail("你找不到 " + from + " 這樣東西。\n");
                if(wizardp(me) && living(env) && (wiz_level(me) <= wiz_level(env))
                 && !query("ridable", env) && env->query_lord() != me )
                        return notify_fail("你的巫師等級必須比對方高，才能搜身。\n");
        } 
        else env = environment(me);
        
        // 不能在睡房裏拿睡覺人的東西
        if (!wizardp(me) && living(env) && env->query_lord() != me)
                return notify_fail("光天化日的想搶劫啊？\n");
        else if( !wizardp(me) && query("no_get_from", env) )
                return notify_fail("邊上有人看着呢，不如等人家醒了搶劫吧！\n");

        // Check if a certain amount is specified.
        if(sscanf(arg, "%d %s", amount, item)==2) {
                if( !objectp(obj = present(item, env)) )
                        return notify_fail("這裏沒有這樣東西。\n");
                if( !obj->query_amount() )
                        return notify_fail( obj->name() + "不能被分開拿走。\n");
                if( amount < 1 )
                        return notify_fail("東西的個數至少是一個。\n");
                if( amount > obj->query_amount() )
                        return notify_fail("這裏沒有那麼多的" + obj->name() + "。\n");
                else if( amount == (int)obj->query_amount() ) {
                        return do_get(me, obj);
               }else {
                        newa = (int)obj->query_amount();
                        obj->set_amount( amount );
                        obj2 = new(base_name(obj));
                        do_get(me, obj);
                        obj2->set_amount(newa - amount);
                        obj2->move(env);                        // For containers.
                        // Counting precise amount costs more time.
                        if( me->is_fighting() ) me->start_busy(3);
                        return 1;
                }
        }

        // Check if we are makeing a quick get.
        if(arg=="all") {
                if( me->is_fighting() ) return notify_fail("你還在戰鬥中！只能一次拿一樣。\n");
                if( !env->query_max_encumbrance() )     return notify_fail("那不是容器。\n");

                inv = all_inventory(env);
                if( !sizeof(inv) )
                        return notify_fail("那裏面沒有任何東西。\n");

                for(i=0; i<sizeof(inv); i++) {
                        if( inv[i]->is_character() || query("no_get", inv[i]))continue;
                        do_get(me, inv[i]);
                }
                write("撿好了。\n");
                return 1;
        }

        if( !objectp(obj = present(arg, env)) || living(obj) )
                return notify_fail("你附近沒有這樣東西。\n");

// 修改一下這裏的描述。
        if( query("no_get", obj) )
    {
        no_get_message=query("no_get", obj);
        if(!stringp(no_get_message) || no_get_message=="1") return notify_fail("這個東西拿不起來。\n");
        else return notify_fail(no_get_message+"\n");
    }

        return do_get(me, obj);
}
       
int do_get(object me, object obj)
{
        object old_env, *enemy;
        int equipped;
        string amt,no_get_message;

        if( !obj ) return 0;
        old_env = environment(obj);

        if( obj->is_character() ) {
                if( living(obj) ) return 0;
                //      if( !userp(obj) && !obj->is_corpse() )
                //              return notify_fail("你只能揹負其他玩家的身體。\n");
                // If we try to save someone from combat, take the risk :P
        }
    else if( query("no_get", obj) )
    {
        no_get_message=query("no_get", obj);
        if(!stringp(no_get_message) || no_get_message=="1") return notify_fail("這個東西拿不起來。\n");
        else return notify_fail(no_get_message+"\n");
    }

        if( query("equipped", obj))equipped=1;
        if( obj->query_amount()) amt = chinese_number(obj->query_amount());
        if( obj->move(me) ) {
                if( me->is_fighting() ) me->start_busy(1);
                if( obj->is_character() )
                        message_vision( "$N將$n扶了起來背在背上。\n", me, obj );
                else
                        message_vision( sprintf("$N%s%s%s$n。\n", 
                                old_env==environment(me)? "撿起":
                                        (old_env->is_character() ?
                                                "從" + old_env->name() + "身上" + (equipped? "除下" : "搜出"):
                                                "從" + old_env->name() + "中拿出"),
                                obj->query_amount()? amt : "一", 
                                obj->query_amount()?query("base_unit", obj):query("unit", obj)),me,obj);
                return 1;
        }
        else return 0;
}

int help(object me)
{
        write(@HELP
指令格式 : get <物品名稱> [from <容器名>]
 
這個指令可以讓你撿起地上或容器內的某樣物品.
 
HELP
    );
    return 1;
}
 