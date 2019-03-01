// zhaixinggong.c 摘星功
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "$n一個"HIW"「天外摘星」"NOR"，躍起數尺，躲過了$N這一招。\n",
        "$n身形向後一縱，使出一招"HIC"「飄然出塵」"NOR"，避過了$N的攻擊。\n",
        "$n使出"HIG"「天狼涉水」"NOR"，恰好躲過了$N的攻勢。\n",
        "$n一招"HIW"「織女穿梭」"NOR"，姿態美妙地躲了開去。\n"
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<10 || query("neili", me)<2 )
                return notify_fail("你的體力太差了，不能摘星功。\n");
        me->receive_damage("qi", 10);
        addn("neili", -2, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n摘星功："NOR"\n");
        write(@HELP

    摘星功是星宿派本門輕功身法。

        學習要求：
          化功大法10級
HELP
        );
        return 1;
}
