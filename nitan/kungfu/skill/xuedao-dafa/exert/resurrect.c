// resurrect.c 浴血重生

#include <ansi.h>

#define R "「" HIR "浴血重生" NOR "」"

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;
        string msg;
        mapping my;
        int rp;
        int neili_cost;

        if( userp(me) && !query("can_perform/xuedao-dafa/resurrect", me) )
                return notify_fail("你所學的內功中沒有這種功能。\n");

        if ((int)me->query_skill("xuedao-dafa", 1) < 120)
                return notify_fail("你的血刀大法不夠深厚，難以施展" R "。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不足，難以施展" R "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" R "。\n");

        my = me->query_entire_dbase();
        if ((rp = (my["max_qi"] - my["eff_qi"])) < 1)
                return (SKILL_D("force") + "/recover")->exert(me, target);

        if (rp >= my["max_qi"] / 10)
                rp = my["max_qi"] / 10;

        skill = me->query_skill("xuedao-dafa", 1);
        msg = HIR "$N" HIR "深深吸入一口氣，臉色由紅轉白，復又由白翻"
              "紅，傷勢恢復了不少。\n" NOR;
        message_combatd(msg, me);

        neili_cost = rp + 100;
        if (neili_cost > my["neili"])
        {
                neili_cost = my["neili"];
                rp = neili_cost - 100;
        }
        me->receive_curing("qi", rp);
        me->receive_healing("qi", rp * 3 / 2);
        addn("neili", -neili_cost, me);

        if (random(10) < 3)
        {
                tell_object(me, HIC "由於你過度的催動真元，導致你的內"
                                "力有所損耗。\n" NOR);
                addn("max_neili", -1, me);
        }
        me->start_busy(3);
        return 1;
}