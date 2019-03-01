// xinghui-canlan.c 星輝燦爛
// By haiyan

inherit SKILL;

int valid_enable(string usage) { return usage == "throwing"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("riyue-xinfa", 1) < 100)
                return notify_fail("你的內功心法火候不夠，無法學星輝燦爛。\n");

        if ((int)me->query_skill("dodge", 1) < 100)
                return notify_fail("你的輕功火候不夠，無法領悟星輝燦爛。\n");

        if ((int)me->query_dex() < 30)
                return notify_fail("你的身法不夠靈巧，無法領悟星輝燦爛。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("mantianhuayu-zhen", 1))
                return notify_fail("你的基本暗器水平有限，難以領會更高深的星輝燦爛。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練星輝燦爛。\n");

        me->receive_damage("qi", 45);
        addn("neili", -45, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xinghui-canlan/" + action;
}
