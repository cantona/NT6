// free.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob;
        object card;
        string tstr;
        string unit;
        int time;

        if (! arg)
                return notify_fail("你要把誰帶出地獄？\n");

        time = 0;
        if (sscanf(arg, "%s %s", arg, tstr) == 2)
        {
                if (sscanf(tstr, "%d%s", time, unit) != 2)
                {
                        sscanf(tstr, "%d", time);
                        unit = "";
                }

                switch (unit)
                {
                case "h": time *= 60;   break;
                case "d": time *= 1440; break;
                }
        }

        ob = find_player(arg);
        if (! ob && wiz_level(me) < 1)
                return notify_fail("沒有這個玩家。\n");

        if (! ob)
        {
                ob = UPDATE_D->global_find_player(arg);
                if (! objectp(ob))
                        return notify_fail("沒有這個玩家。\n");

                ob->move(environment(me));
        }

        if (! ob || ! me->visible(ob))
        {
                UPDATE_D->global_destruct_player(ob);
                return notify_fail("沒有這個玩家。\n");
        }

        if (! ob->is_in_prison())
        {
                UPDATE_D->global_destruct_player(ob);
                return notify_fail("這個玩家現在沒有被禁閉。\n");
        }

        if (! SECURITY_D->valid_grant(me, "(arch)"))
        {
                if (! objectp(card = present("help card", me)))
                        return notify_fail("你沒有權利把人放出來。\n");

                message_vision("$N摸出一張卡片，拼命唸叨：太上老君救命啊，" +
                               ob->name(1) + "真是無辜啊！\n", me);
                destruct(card);
        }

        ob->leave_prison(me, time);
        UPDATE_D->global_destruct_player(ob, 1);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : free <玩家ID> [ <時間> ]
 
這個指令可以讓你把被禁閉的玩家釋放出來。時間以分鐘為單位，可
以用 h 表示小時，d 表示天。

see also : throw
 
HELP );
        return 1;
}