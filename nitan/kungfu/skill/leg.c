// leg.c 基本腿法
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

string type() { return "martial"; }
string martialtype() { return "skill"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int help(object me)
{
        write(HIC"\n基本腿法："NOR"\n");
        write(@HELP

    腿法類武技的基本功。

        學習要求：
                無
HELP
        );
        return 1;
}
