// time.c                                          
#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int cur_time = time();  

        if( !wizardp(me) && cur_time-query_temp("last_who", me)<5 )
                return notify_fail("系統氣喘噓地歎道：慢慢來 ....\n");  

        set_temp("last_who", cur_time, me);
        if (! objectp(WAR_D->query_marshal()))
                return notify_fail("現在前方沒有戰事！\n"); 

        write(sprintf("王朝戰爭已經進行了" + WAR_D->query_continue_time() + "。\n"));
        return 1;
}

int help(object me)
{
     write(@HELP
指令格式: time

這個指令告訴你王朝戰爭已經進行的時間。

HELP
    );
    return 1;
}