// qingzi9da.c 青字九打
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

string type() { return "knowledge"; }
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

void skill_improved(object me) {}

int valid_learn(object me)
{
        if(me->query_skill("qingming-xuangong", 1)  <
                me->query_skill("qingzi9da", 1))
                return notify_fail("你的本門內功未到火候，無法繼續修習青字九打。\n");
        return 1;
}

int help(object me)
{
        write(HIC"\n青字九打："NOR"\n");
        write(@HELP

    “青字九打”與“城字十八破”並列為青城鎮山武功，配套兵
器是青蜂釘。

        學習要求：
                相應級別的青冥玄功
HELP
        );
        return 1;
}
