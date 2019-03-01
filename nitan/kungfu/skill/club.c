// club.c 基本棍法
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
        write(HIC"\n基本棍法："NOR"\n");
        write(@HELP

    棍類武技的基本功。
    所謂“槍紮一條線，棍打一大片”，一掃一劈全身著力。棍練
起來虎虎生風，節奏生動，棍法密集，快速勇猛。它既能強身健體，
又能克敵制勝，在歷代抗敵御侮中，少林棍發揮過重要的作用。 

        學習要求：
                無
HELP
        );
        return 1;
}
