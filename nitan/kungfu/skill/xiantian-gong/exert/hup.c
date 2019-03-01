// This program is a part of NITAN MudLIB
// hup.c 五氣朝元

#include <ansi.h>

#define HUP "「" HIR "五氣朝元" NOR "」"

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;
        string msg;
        mapping my;
        int rp;
        int neili_cost;

        if( userp(me) && !query("can_perform/xiantian-gong/hup", me) )
                return notify_fail("你未得高人指點，不知該如何施展" HUP "。\n"); 

        if ((int)me->query_skill("xiantian-gong", 1) < 200)
                return notify_fail("你先天功不夠深厚，難以施展" HUP "。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不足，難以施展" HUP "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" HUP "。\n");

        my = me->query_entire_dbase();
        if ((rp = (my["max_qi"] - my["eff_qi"])) < 1)
                return (SKILL_D("force") + "/recover")->exert(me, target);

        if (rp >= my["max_qi"] / 10)
                rp = my["max_qi"] / 10;

        skill = me->query_skill("force");
        msg = HIW "$N" HIW "緩緩吐出一口氣，頓時氣脈通暢，臉色漸漸的變"
              "得平和。\n" NOR;
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

        me->start_busy(3);
        return 1;
}