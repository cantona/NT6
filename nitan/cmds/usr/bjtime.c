// time.c                                          
#include <ansi.h>

// #define END_TIME 874425565
#define END_TIME 875981023
#define FETEDAY "中秋節"
inherit F_CLEAN_UP;

int main(object me, string arg)
{   int time, date;
    time = time();
        write(sprintf("現在的時間是北京時間 " + ctime( time ) + "。\n"));
    date = (END_TIME-time) / 24 / 3600;
    if (date > 1)
    {
        write(sprintf("距離" + FETEDAY + "還有"BBLU YEL"%s"NOR"天。\n", 
            chinese_number(date)));
    }
    else if (date == 1)
    {
        write(sprintf(BBLU YEL "\n\t\t明天就是" + FETEDAY + "了！\n\n" NOR));
    }
    else if (!date)
    {
        write(sprintf(BBLU YEL "\n\t\t今天是" + FETEDAY + "！\n\n"NOR));
    }
        return 1;
}

int help(object me)
{
     write(@HELP
指令格式: time

這個指令告訴你現實世界中現在的時間。

HELP
    );
    return 1;
}