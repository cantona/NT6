// training.c 馭獸術
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "knowledge"; }

int learn_bonus() { return 15; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1; }

int help(object me)
{
        write(HIC"\n馭獸術："NOR"\n"); 
        write(@HELP

    馭獸術是驅使動物的技能。唯丐幫弟子和白駝山弟子能學到。
    請help train和help transport。

        學習要求：
                無
HELP
        );
        return 1;
}
