// steal.c

#include <ansi.h>
#include <config.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string what, who;
        object env;
        object ob, victim;
        mapping myfam, vtfam;
        int sp, dp;

        env = environment(me);
        if( query("no_fight", env) )
                return notify_fail("這裏禁止行竊。\n");

        if( query("no_steal", env) )
                return notify_fail("這裏禁止行竊。\n");

        if( query_temp("stealing", me) )
                return notify_fail("你已經在找機會下手了！\n");

        if (me->is_busy())
                return notify_fail("你現在正忙，沒有時間。\n");

        if (! arg || sscanf(arg, "%s from %s", what, who) != 2)
                return notify_fail("指令格式：steal <物品> from <人物>\n");

        victim = present(who, environment(me));
        if (! victim || victim == me)
                return notify_fail("你想行竊的對象不在這裏。\n");

        if( !me->visible(victim) )
                return notify_fail("你看不到"+query("name", victim)+"。\n");

        if (! victim->is_character())
                return notify_fail("你看清楚了，那不是活人！");

        if( query_temp("sleeped", victim) )
                return notify_fail("他雖然在睡覺，但警覺性還是很高，你無法下手！");

        if (victim->query_competitor())
                return notify_fail("人家正在比武，你搗什麼亂？\n");

        if (! wizardp(me) && wizardp(victim))
                return notify_fail("玩家不能偷巫師身上的東西。\n");

        if( query("jing", me)<80 )
                return notify_fail("你現在難以集中精神，不敢貿然下手偷竊。\n");

        if (! ob = present(what, victim))
        {
                object *inv;
                inv = all_inventory(victim);
                if (! sizeof(inv))
                        return notify_fail(victim->name() + "身上看起來沒有什"
                                           "麼值錢的東西好偷。\n");
                ob = inv[random(sizeof(inv))];
        }

        sp = (int)me->query_skill("stealing") * 5 -
             query("thief", me)*20;

        if( (myfam=query("family", me)) && myfam["family_name"] == "丐幫" )
                sp = (int)me->query_skill("stealing") * 10 -
                     query("thief", me)*20;

        if (sp < 1) sp = 1;

        if (me->is_fighting())
        {
                sp /= 2;
                me->start_busy(3);
        }
        dp=query("jing", victim)*2+ob->weight()/25;
        if (victim->is_fighting()) dp *= 10;
        if( query("equipped", ob))dp*=20;

        write("你不動聲色地慢慢靠近" + victim->name() + 
              "，等待機會下手 ...\n\n");

        if( query("newbie", me) && playerp(victim) )
        {
                set("no_newbie", 1, me);
                delete("newbie", me);
                tell_object(me, HIR "由於你偷竊其他玩家物品，所以取消對你的新手保護！\n" NOR);
        }

        set_temp("stealing", 1, me);
        me->start_call_out((: call_other, __FILE__, "compelete_steal", me, victim, ob, sp, dp :), 3);

        return 1;
}

void compelete_steal(object me, object victim, object ob, int sp, int dp)
{
        mapping myfam, vtfam;
        int steal_level;

        if (! objectp(me))
                return;

        delete_temp("stealing", me);

        if (! objectp(victim) || environment(victim) != environment(me))
        {
                tell_object(me, "太可惜了，你下手的目標已經走了。\n");
                return;
        }

        if( query_temp("sleeped", victim) )
        {
                tell_object(me, "他雖然在睡覺，但警覺性還是很高，你無法下手！\n");
                return;
        }

        if (! objectp(ob))
                return;

        if (environment(ob) != victim)
        {
                tell_object(me, "你摸了半天，發現" + ob->name() +
                            "已經不在那裏了。\n");
                return;
        }

        if (! living(victim) || (random(sp + dp) > dp))
        {
                if( query_temp("is_riding", victim) == ob )
                {
                        tell_object(me, "你摸到了" + victim->name() + "坐騎" + ob->name() +
                                    "，想了想，還是老老實實的放了手。\n");
                        return;
                }

                if( query("no_steal", ob) )
                {
                        tell_object(me,"你摸到一"+query("unit", ob)+ob->name()+
                                    "，可是你突然作賊心虛，居然不敢下手，真是可惜了。\n");
                        return;
                }

                if (sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED)
                {
                        tell_object(me, "眼看你就要得手，可惜身上的東"
                                    "西太多，實在拿不了了。\n");
                        ob->move(environment(me));
                        return;
                }

                if (! ob->move(me))
                {
                        tell_object(me,"你摸到一"+query("unit", ob)+ob->name()+
                                    "，可是對你而言太重了，不得不放棄。\n");
                        return;
                }

                tell_object(me, HIW "得手了！\n\n" NOR);
                tell_object(me,"你成功地偷到一"+query("unit", ob)+
                            ob->name() + "！\n");
                steal_level = (int)me->query_skill("stealing",1);

                if (living(victim))
                {
                        if (me->can_improve_skill("stealing"))
                                me->improve_skill("stealing",random(query("int", me)));

                        if( query("potential", me)<me->query_potential_limit() )
                        addn("potential", 1, me);

                        addn("thief", 1, me);
                        me->receive_damage("jing", 10);
                        addn("combat_exp", 1, me);
                }

                if (random(sp) < dp / 2)
                        message("vision", "你看到" + me->name() + "鬼鬼祟祟地從" +
                                victim->name()+"身上偷走了一"+query("unit", ob)+
                                ob->name() + "！\n", environment(me), ({ me, victim }));
        } else
        {
                if (random(sp) > dp / 2)
                {
                        tell_object(me, victim->name() + "不經意地一轉頭，你"
                                    "急忙將手縮了回去！\n還好，沒有被發現！\n");
                        return;
                }

                tell_object(me, HIR "糟糕！你失手了！\n\n" NOR);
                message_vision("$N一回頭，正好發現$n的手正抓着$P身上的" +
                               ob->name() + "！\n$N喝道：「幹什麼！」\n",
                               victim, me);
                me->improve_skill("stealing", 1, 1);

                if (userp(victim))
                {
                        message_vision("$N狠狠的敲着$n的頭，嚇得$n嗚嗚直叫。\n",
                                       victim, me);
                } else
                {
                        victim->kill_ob(me);
                        me->fight_ob(victim);
                }

                if (! me->is_busy()) me->start_busy(3);
                addn("thief", 1, me);
                me->receive_damage("jing", 15 + random(10));
        }
}

int help(object me)
{
        write(@HELP
指令格式 : steal <某物> from <某人>

這個指令讓你有機會偷到他人身上的東西。成功了, 當然你就能獲得
該樣物品。可是, 馬有失蹄, 人總有失風的時候, 當你失敗時當然就
得付出代價, 至於是什麼代價......靠你自己去發掘羅。
HELP );
        return 1;
}