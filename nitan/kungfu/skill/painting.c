// painting.c 潑墨丹青
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

        lvl = (int)me->query_skill("painting", 1);

        if( lvl>29 && query("kar", me) != 28 )
                return notify_fail("限于天資，你只能修習這個程度了。\n");
        else return 1;
}

int practice_skill(object me)
{
        return notify_fail("潑墨丹青只能靠學習來提高。\n");
}
int help(object me)
{
        write(HIC"\n潑墨丹青："NOR"\n");
        write(@HELP

    逍遙派祖師逍遙子學究天人，胸中所學包羅萬象。他共傳下七
門絕藝：繞樑琴藝 (luteplaying)、紋枰手談 (goplaying)、潑墨
丹青(painting)、濟世之術(medicine)、土木機關(construction)、
園藝蒔花(horticulture)、梨園舊藝(dramaturgy)。

        學習要求：
                無。但天賦才氣限制了對更高深境界的努力
HELP
        );
        return 1;
}
