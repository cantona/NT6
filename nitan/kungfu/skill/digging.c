// digging.c 掘地之術
// Last Modified by winder on Jun. 10 2000

#include <ansi.h>;
inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int valid_learn(object me)
{
        int lvl;

        lvl = (int)me->query_skill("construction", 1);

        if( lvl>29 && query("kar", me) != 27 )
                return notify_fail("限于天資，你只能修習這個程度了。\n");
        else return 1;
}

int practice_skill(object me)
{
        return notify_fail("掘地之術只能靠學習來提高。\n");
}
int help(object me)
{
        write(HIC"\n掘地之術："NOR"\n");
        write(@HELP

    掘地之術是神龍島獨門絕技。

        學習要求：
                無。
HELP
        );
        return 1;
}
