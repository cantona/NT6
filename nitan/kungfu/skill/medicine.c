// medicine.c 濟世之術
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

        lvl = (int)me->query_skill("medicine", 1);

        if( query("age", me)<16 )
                return notify_fail("你的年紀太輕，無法修習濟世之術。\n");

        if( !query("medicine", me) )
        {
                if (random(6) == 1)
                {
                        set("medicine", 2, me);
                }
                else
                {
                        set("medicine", 1, me);
                }
        }
        if( lvl>29 && query("medicine", me) == 1 )
                return notify_fail("限於天資，你只能修習這個程度了。今後還是努力練功，自求多福吧。\n");
        else return 1;
}

int practice_skill(object me)
{
        return notify_fail("濟世之術只能靠學習來提高。\n");
}
int help(object me)
{
        write(HIC"\n濟世之術："NOR"\n");
        write(@HELP

    逍遙派祖師逍遙子學究天人，胸中所學包羅萬象。他共傳下七
門絕藝：繞樑琴藝 (luteplaying)、紋枰手談 (goplaying)、潑墨
丹青(painting)、濟世之術(medicine)、土木機關(construction)、
園藝蒔花(horticulture)、梨園舊藝(dramaturgy)。
    精通濟世之術，可以採藥煉丹、練功治病。請help medical。

        學習要求：
                無。但天賦才氣限制了對更高深境界的努力
HELP
        );
        return 1;
}
