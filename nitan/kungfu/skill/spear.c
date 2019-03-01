// spear.c 基本槍法
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
        write(HIC"\n基本槍法："NOR"\n");
        write(@HELP

    槍類武技的基本功。
    槍是歷代重要兵器之一，為「百兵之王」。武林中人稱「百日
刀、千日槍、萬日劍」，上陣沖鋒槍為首選。

        學習要求：
                無
HELP
        );
        return 1;
}
