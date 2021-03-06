// winfo.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string str;

        seteuid(getuid());

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        str = WORK_D->query_all_work();
        me->start_more(str);

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : qinfo [<任務名稱>]

此指令可查看當前系統有的任務。
HELP );
        return 1;
}