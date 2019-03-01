#include <ansi.h>

inherit SKILL;

int valid_enable(string usage)
{
        return usage == "throwing";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 90)
                return notify_fail("你的內功火候不夠，難以修煉破滅金針。\n");

        if ((int)me->query_skill("dodge") < 90)
                return notify_fail("你的輕功火候不夠，難以修煉破滅金針。\n");

        if ((int)me->query_dex() < 25)
                return notify_fail("你的身法靈動不夠，難以修煉破滅金針。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("pomie-jinzhen", 1))
                return notify_fail("你的基本暗器水平有限，難以領會更高深的破滅金針。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練破滅金針。\n");

        me->receive_damage("qi", 45);
        addn("neili", -45, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"pomie-jinzhen/" + action;
}