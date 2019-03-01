// finduser

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        object link_ob;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if( !arg )
                return notify_fail("argument error!\n");

        ob = find_player(arg);
        if (!ob)
        {
                write ("咦... 沒有這個人呀?\n");
                return 1;
        }

        printf("User(%s) has found as %O\nuid = %s  euid = %s\n",
               arg, ob, getuid(ob), geteuid(ob));
        if( objectp(link_ob=query_temp("link_ob", ob)) )
                printf("Link object has also found as %O\nuid = %s euid=%s\n",
                       link_ob, getuid(link_ob), geteuid(link_ob));
        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : finduser <某人>

找到某人的內存中的對象，並顯示他的標識和有效標識。這是一條用來排
除故障的調試命令。

相關命令：call

HELP
    );
    return 1;
}