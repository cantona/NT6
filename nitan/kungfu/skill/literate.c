// literate.c 讀書寫字
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

string type() { return "knowledge"; }
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 20; }
int power_point(object me) { return 1; }

void skill_improved(object me)
{}

int valid_learn(object me)
{
//        if ( me->query("class") != "bonze" )
//                return notify_fail("你現在不能學習讀書寫字。\n");
        return 1;
}

int help(object me)
{
        write(HIC"\n讀書寫字："NOR"\n");
        write(@HELP

    讀書寫字是自學武籍的基礎，並能改善你後天的悟性。

        學習要求：
                無
HELP
        );
        return 1;
}
