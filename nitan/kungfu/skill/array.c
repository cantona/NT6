// array.c
// Last Modified by winder on Mar. 10 2000

//#include <ansi.h>;
inherit SKILL;

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }
/*
int help(object me)
{
        write(HIC"\n基本陣法："NOR"\n");
        write(@HELP

    桃花島弟子布陣所用基本技能。

        學習要求：
                無
HELP
        );
        return 1;
}
*/