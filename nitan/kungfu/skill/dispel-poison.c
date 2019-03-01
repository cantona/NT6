// shedu-qiqiao.c

inherit SKILL;

int valid_enable(string usage) { return usage == "poison"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候不夠，無法學習妙手驅毒。\n");

        if( query("max_neili", me)<350 )
                return notify_fail("你的內力太弱，無法學習妙手驅毒。\n");

        if ((int)me->query_skill("poison", 1) < 30)
                return notify_fail("你的基本毒技火候不夠，無法學妙手驅毒。\n");

        if ((int)me->query_skill("poison", 1) < (int)me->query_skill("dispel-poison", 1))
                return notify_fail("你的基本毒技水平有限，無法領會更高深的妙手驅毒。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("妙手驅毒只能通過學習獲得長進。\n");
}