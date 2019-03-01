// attack.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object env;
        object ob, *inv;
        int i;

        seteuid(getuid());

        if( query("no_fight", (env=environment(me))) )
                return notify_fail("這裡不許打鬥！\n");

        if( query("jing", me) <= 30 )
                return notify_fail("現在你太累了，無法讓野獸幫你咬人。\n");

        if (! arg)
                return notify_fail("你要讓什麼野獸幫你咬誰？\n");

        if (! objectp(ob = present(arg, env)))
                return notify_fail("這裡沒有這個東西吧？\n");

        inv = all_inventory(env);
        i = sizeof(inv);
        while (i--)
        {
                if (inv[i] == ob)
                        continue;

                if( !inv[i]->is_character() || query("can_speak", inv[i]) )
                        continue;

                if( query_temp("owner", inv[i]) == query("id", me) )
                {
                        if (inv[i]->is_fighting())
                                return notify_fail("已經有野獸在幫你咬人了！\n");

                        if (inv[i]->is_busy())
                                return notify_fail(inv[i]->name() +
                                                   "正在忙乎，沒空理你！\n");

                        if (me->query_skill("training", 1) < 30)
                                return notify_fail("你的馭獸術還不純熟，無法"
                                                   "讓野獸幫你咬人！\n");

                        message_vision("只見$N沖著" +inv[i]->name()+
                                       "口中一聲呼哨，它一竄就向$n撲了上去。\n",
                                       me, ob);
                        me->receive_damage("jing", 30);
                        me->want_kill(ob);
                        inv[i]->fight_ob(ob);
                        return 1;
                }
        }

        write("附近沒有你可以驅使的對象。\n");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : attack <動物>

此指令可用于讓某動物幫你攻擊，咬別人。對于已經馴服的動物，可以進行
下述指令：

基本指令：
        come <動物名>:                  讓動物跟隨主人行動。
        stay:                           停止動物的跟隨狀態。
        attack <某人>:                  讓動物攻擊敵人。
        stop <動物名>:                  讓動物停止對人的攻擊。
        release:                        結束主奴狀態，將動物放離。

特殊指令：（只對某些動物適用）
        qi(ride) <動物名>:              騎，如騎馬，虎，雕，鯊等。
        xia(unride) <動物名>:           下，離開坐騎。

HELP );
        return 1;
}
