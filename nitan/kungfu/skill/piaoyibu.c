// piaoyibu.c 飄逸步法
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype(object me) { return "dodge"; }

string *dodge_msg = ({
        "$n一個"HIC"「銀鷺渡海」"NOR"，躍起數尺，躲過了$N這一招。\n",
        "$n身形向後一縱，使出一招"HIY"「玉兔落塵」"NOR"，避過了$N的攻擊。\n",
        "$n使出"HIY"「錦鯉穿沙」"NOR"，恰好躲過了$N的攻勢。\n",
        "$n一招"MAG"「靈狐幻遁」"NOR"，姿態美妙地躲了開去。\n"
});

int valid_enable(string usage) { return usage == "dodge" || usage == "move"; }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<10 || query("neili", me)<2 )
                return notify_fail("你的體力太差了，不能練飄逸步法。\n");
        me->receive_damage("qi", 10);
        addn("neili", -2, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 20; }
int power_point(object me) { return 1.1; }

int help(object me)
{
        write(HIC"\n飄逸步法："NOR"\n");
        write(@HELP

    日月神教黑木崖本門輕功。

        學習要求：
          葵花心法10級
HELP
        );
        return 1;
}
