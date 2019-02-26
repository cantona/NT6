// taoism.c 道學心法
// Last Modified by winder on Mar. 10 2000

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

        lvl = (int)me->query_skill("taoism", 1);

        if( query("gender", me) == "無性" && lvl>19 )
                return notify_fail("你剛聽一會兒，便覺心智迷糊，原來你沒有陽剛之\n"
                           "氣，無法領會裏面的陰陽變化之道。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("道學心法只能靠學習來提高。\n");
}

int help(object me)
{
        write(HIC"\n道學心法："NOR"\n");
        write(@HELP

    太上道祖傳下的道德真言五千字中藴涵的博大精深的心法。
    可尋找道德經閲讀。

        學習要求：
                與禪宗心法、密宗心法、紫氲吟、正氣訣和基本毒技不能兼學
HELP
        );
        return 1;
}
