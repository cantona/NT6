// yunlong-xinfa.c 雲龍心法
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int practice_skill(object me)
{        
        return notify_fail("雲龍心法只能靠學(learn)來提高。\n");
}
int help(object me)
{
        write(HIC"\n雲龍心法："NOR"\n");
        write(@HELP

    雲龍心法是雲龍門的精神支柱。用以激勵天地會眾反清復明。

        學習要求：
                無
HELP
        );
        return 1;
}
