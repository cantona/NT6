// force.c 基本內功
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }
int valid_learn(object me) {return 1;}

string exert_function_file(string func)
{
        return __DIR__"force/" + func;
}

void skill_improved(object me)
{}
int help(object me)
{
        write(HIC"\n基本內功："NOR"\n");
        write(@HELP

    基本內功是所有武功的基礎，並能改善你後天的根骨。
    請help neigong。

        學習要求：
                無
HELP
        );
        return 1;
}
