// necromancy.c 降伏法
// Last Modified by winder on Mar. 10 2000
// by Java

#include <ansi.h>;
inherit SKILL;
string type() { return "knowledge"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1; }

int valid_learn(object me)
{
        if( (int)me->query_skill("longxiang",1) <
                (int)me->query_skill("necromancy",1) )
                return notify_fail("你的龍相般若功太低了，無法修煉更高深的降伏法。\n");
        return 1;
}
int practice_skill(object me)
{
        return notify_fail("降伏法只能靠學(learn)來提高。\n");
}

int help(object me)
{
        write(HIC"\n降伏法："NOR"\n");
        write(@HELP

    降伏法為密宗密技，身為密宗弟子，且有相當的降伏法修為，
可利用懾心術誘惑某人做把身上的東西給你, 或往那裏離開，或者
跟着你。對方如果內功深厚，而你學藝不精，必然也會招致以牙還
牙。
    請help shexin。

        學習要求：
                龍象般若功等級不能低於降伏法等級
HELP
        );
        return 1;
}
