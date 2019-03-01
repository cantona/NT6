// telnet

#include <ansi.h>
#include <net/dns.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        mapping minfo;
        mapping m;
        string *msg;
        object tob;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        seteuid(getuid());

        if (! arg)
                return notify_fail("你要連接哪裡？\n");

        m = fetch_variable("mudlist", get_object(INTERMUD2_D));
        if( sizeof(msg = INTERMUD2_D->fetch_mudname(arg,1)) ) 
        {
                foreach(string a in msg) 
                        minfo = copy(m[a]);
                arg = minfo["HOSTADDRESS"] + " " + minfo["PORT"];
                write("連接" + minfo["NAME"] + "(" + arg + ")\n");
        } else
        if (sscanf(arg, "%*s %*s") != 2)
                arg += " 23";

        tob = new("/shadow/telnet3");
        if (tob->do_shadow(me, 1) != me)
        {
                write("系統錯誤，映射失敗。\n");
                return 1;
        }

        tob->connect_to(arg);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式: telnet <MUD> | <主機地址> [<目的端口>]

這個指令讓你可以連接另外一個服務器。

連接時輸入 CLOSE 命令可以終止連接。

HELP );
        return 1;
}
