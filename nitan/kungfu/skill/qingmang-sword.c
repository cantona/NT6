// qingmang-sword.c 青蟒劍法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *msg = ({
        "$N刷刷刷連出三招，使出「青蟒吐信」，但見$w閃動，猶如蟒蛇吐信一般，不知要劈向何處",
        "$N得理不讓人，又是一招，$w直揮$n面門，逼得$n急忙側頭避讓",
        "$N左腳又在$n小腿上一掃，想將$n拌倒，跟着$w一抖，已指住$n咽喉",
        "$N一聲冷笑，手中$w迎面砍下，直劈$n$l",
        "$N一下衝到$n身前，突然之間拔出$w，便往$n頭上砍了下去",
        "$N突然一下拔$w揮擊，既是突如其來，行動又是快極，$n全無閃避的餘裕",
        "$N$w挺出，一招「毒蛇出洞」，向$n當胸劈去，勢道甚是勁急",
        "$N叫聲：「好！」$w圈轉，削向$n$l",
        "$N一招「靈舌吐信」，$w尖快絕無比點向$n的$l"
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");
        if ((int)me->query_skill("wudu-shengong", 1) < 20)
                return notify_fail("你的五毒神功火候太淺。\n");
        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("你的基本內功火候太淺。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<30
         || query("neili", me)<15 )
                return notify_fail("你的內力或氣不夠練青蟒劍法。\n");
        me->receive_damage("qi", 30);
        addn("neili", -10, me);
        return 1;
}
mapping query_action(object me, object weapon)
{
        return ([
                "action" : msg[random(sizeof(msg))],
                "damage" : 30+random(100),
                "dodge"  : 30+random(25),
                "parry"  : 5+random(15),
                "force"  : 50+random(50),
                "damage_type" : random(2)?"刺傷":"割傷",
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n青蟒劍法："NOR"\n");
        write(@HELP

    青蟒劍法是五毒劍法的一種。

        學習要求：
                基本內功20級
                五毒神功20級
                內力100
HELP
        );
        return 1;
}
