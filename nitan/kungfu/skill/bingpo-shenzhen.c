#include <ansi.h>

inherit SKILL;

int valid_enable(string usage) 
{ 
       return usage == "throwing"; 
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功心法火候不夠，無法學冰魄神針。\n");

        if ((int)me->query_skill("dodge") < 100)
                return notify_fail("你的輕功火候不夠，無法領悟冰魄神針。\n");

        if ((int)me->query_dex() < 34)
                return notify_fail("你的身法不夠靈巧，無法領悟冰魄神針。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("bingpo-shenzhen", 1))
                return notify_fail("你的基本暗器水平有限，難以領會更高深的冰魄神針。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( query("qi", me)<80 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練冰魄神針。\n");

        me->receive_damage("qi", 72);
        addn("neili", -65, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"bingpo-shenzhen/" + action;
}