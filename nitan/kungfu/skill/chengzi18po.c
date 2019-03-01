// chengzi18po.c 城字十八破
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

string type() { return "knowledge"; }
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point() { return 1; }

void skill_improved(object me) {}

int valid_learn(object me)
{
        if(me->query_skill("qingming-xuangong", 1) + random(5) <
                me->query_skill("chengzi18po", 1))
                return notify_fail("你的本門內功未到火候，無法繼續修習城字十八破。\n");
        return 1;
}

int help(object me)
{
        write(HIC"\n城字十八破："NOR"\n");
        write(@HELP

    “城字十八破”與“青字九打”並列為青城鎮山武功，配套兵
器是雷公轟。

        學習要求：
                相應級別的青冥玄功
HELP
        );
        return 1;
}
