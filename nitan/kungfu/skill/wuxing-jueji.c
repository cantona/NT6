// wuxing-jueji.c 五行絕技

#include <ansi.h>

inherit SKILL;

int valid_enable(string usage) { return usage == "throwing"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的內功心法火候不夠，無法學五行絕技。\n");

        if ((int)me->query_skill("dodge") < 80)
                return notify_fail("你的輕功火候不夠，無法領悟五行絕技。\n");

        if ((int)me->query_dex() < 26)
                return notify_fail("你的身法不夠靈巧，無法領悟五行絕技。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("wuxing-jueji", 1))
                return notify_fail("你的基本暗器水平有限，難以領會更高深的五行絕技。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練五行絕技。\n");

        me->receive_damage("qi", 52);
        addn("neili", -35, me);
        return 1;
}