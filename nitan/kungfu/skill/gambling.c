// gambling.c 基本賭技
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

void skill_improved(object me)
{}

int valid_learn(object me)
{
        if( query("age", me) <= 20 )
                return notify_fail("你現在還太小，不能學習基本賭技。\n");
        return 1;
}

int help(object me)
{
        write(HIC"\n基本賭技："NOR"\n");
        write(@HELP

    基本賭技是一種江湖技藝。通過在賭場中賭博，可以用金銀和
技能下注，獲得利益。

        學習要求：
                賭博
HELP
        );
        return 1;
}
