// cookery.c 烹飪手藝
// Last Modified by winder on Jun. 10 2000

#include <ansi.h>;
inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        return notify_fail("烹飪手藝只能靠學習來提高。\n");
}
int help(object me)
{
        write(HIC"\n烹飪手藝："NOR"\n");
        write(@HELP

    烹飪手藝是你宴請玩家的本錢。請help cookery。

        學習要求：
                無。但天賦才氣限制了對更高深境界的努力
HELP
        );
        return 1;
}
