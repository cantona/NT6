inherit SKILL;

int valid_learn(object me)
{
        object ob;

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力不夠，沒有辦法練小李飛刀。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，沒有辦法練小李飛刀。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("xiaoli-feidao", 1))
                return notify_fail("你的基本暗器水平有限，無法領會更高深的小李飛刀。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "throwing";
}

int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("你的氣不夠，沒有辦法練習小李飛刀。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠，沒有辦法練習小李飛刀。\n");

        me->receive_damage("qi", 35);
        addn("neili", -48, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xiaoli-feidao/" + action;
}