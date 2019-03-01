// snoop.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string msg;
        object sob;
        object ob;

        if (! interactive(me))
                return 0;

        if (! arg)
        {
                if (objectp(ob = query_snooping(me)))
                        write("你現在正在監聽"+query("name", ob)+
                              "所收到的訊息。\n");
                else
                        write("你現在沒有監聽任何人。\n");

                return 1;
        } else
        if (arg == "none")
        {
                snoop(me);
                write("Ok.\n");
                return 1;
        } else
        if (sscanf(arg, "-i %s", arg) || arg == "-i")
        {
                if (! SECURITY_D->valid_grant(me, "(admin)"))
                {
                        write("參數錯誤。\n");
                        return 1;
                }

                if (arg == "-i")
                        ob = me;
                else
                        ob = find_player(arg);
                if (! objectp(ob))
                {
                        write("沒有找到 " + arg + " 這個玩家，無法查看信息。\n");
                        return 1;
                }

                msg = "目前有關" + ob->name(1) + "(" + geteuid(ob) + ")的監聽情況如下：\n";
                if (objectp(sob = query_snooping(ob)))
                        msg += "正在監聽" + sob->name(1) + "(" + geteuid(sob) +
                               ")收到的信息。\n";
                else
                        msg += "沒有監聽任何人。\n";

                if (objectp(sob = query_snoop(ob)))
                        msg += "正在被" + sob->name(1) + "(" + geteuid(sob) +
                               ")竊聽。\n";
                else
                        msg += "沒有被任何人竊聽。\n";

                write(msg);
                return 1;
        }

        ob = find_player(arg);
        if (! ob) ob = find_living(arg);
        if (! ob || ! me->visible(ob))
                return notify_fail("沒有這個人。\n");

        if (! interactive(ob))
                return notify_fail("這個玩家不在線上，無法監聽。\n");

        if( !is_sub(query("id", me),query("env/can_snoop", ob)) && 
            ! SECURITY_D->valid_grant(me, "(arch)"))
                return notify_fail("這個玩家不允許你監聽。\n");

        if (wiz_level(ob) > wiz_level(me))
                return notify_fail("你的權限不夠監聽對方。\n");

        if (me == ob) return notify_fail("請用 snoop none 解除監聽。\n");
                
        snoop(me, ob);
        write("你現在開始竊聽" + ob->name(1) + "所收到的訊息。\n");
        /*
        if (playerp(ob)) log_file("snoop",
                sprintf("%s(%s-%s) snoops %s on %s.\n", me->name(1),
                        geteuid(me), query_ip_number(ob), ob->name(1),
                        ctime(time()) ) );
        */

        return 1;
}

int help()
{
        write(@TEXT
指令格式：snoop <某人> | none | -i <某人>

監聽其他使用者所收聽的訊息，snoop none 則取消監聽。你監聽
對方的前提是對方允許你這麼做，即設置了 can_snoop 為你的ID。

使用 -i 參數可以查看某人目前竊聽的信息。
TEXT );
        return 1;
}