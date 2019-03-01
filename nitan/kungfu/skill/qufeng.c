// qufeng.c 驅蜂之術

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
        if ((int)me->query_skill("yunv-xinfa", 1) < 30)
                return notify_fail("你的玉女心法火候不夠，無法學驅蜂之術。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力太弱，無法學習驅蜂之術。\n");

        return 1;
}
int practice_skill(object me)
{
        return notify_fail("驅蜂之術只能靠學習來提高。\n");
}

int help(object me)
{
        write(HIC"\n驅蜂之術："NOR"\n");
        write(@HELP

    古墓弟子如果身具驅蜂術，使用蜂漿瓶即可驅蜂克敵。
    請help qufeng。

        學習要求：
                玉女心法10級
                內力30
HELP
        );
        return 1;
}
