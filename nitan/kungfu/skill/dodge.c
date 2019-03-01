// dodge.c 基本輕功
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

string type() { return "martial"; }
string martialtype() { return "dodge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

string *dodge_msg = ({
        "但是和$p$l偏了幾寸。\n",
        "但是被$p機靈地躲開了。\n",
        "但是$n身子一側，閃了開去。\n",
        "但是被$p及時避開。\n",
        "但是$n已有準備，不慌不忙的躲開。\n",
});

string query_dodge_msg()
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
int help(object me)
{
        write(HIC"\n基本輕功："NOR"\n");
        write(@HELP

    輕功類武技的基本功，並能改善你後天的身法。
    輕功高到一定程度可以輕易渡河(cross)，練習一些特別的輕功
將更為容易達到過河條件。

        學習要求：
                無
HELP
        );
        return 1;
}
