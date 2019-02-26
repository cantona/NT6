#include <ansi.h>
#include <combat.h>

#define DING "「" HIY "定嶽七方" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, ap, dp;

/*
        if( userp(me) && !query("can_perform/zhongping-qiang/ding", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");
*/

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DING "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail("你所使用的武器不對，難以施展" DING "。\n");

        if ((int)me->query_skill("zhongping-qiang", 1) < 120)
                return notify_fail("你中平槍法不夠嫻熟，難以施展" DING "。\n");

        if (me->query_skill_mapped("club") != "zhongping-qiang")
                return notify_fail("你沒有激發中平槍法，難以施展" DING "。\n");

        if ((int)me->query_skill("force") < 180 )
                return notify_fail("你的內功火候不夠，難以施展" DING "。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為不夠，難以施展" DING "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" DING "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "身形一轉，施出中平槍法絕技「" HIR "定嶽七方"
              HIY "」，手中" + weapon->name() + HIY "接連七刺，槍槍不離"
             "$n" HIY "要害！\n" NOR;

        ap = me->query_skill("club");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIR "$n" HIR "見$N" HIR "攻勢兇猛異常，實非"
                       "尋常，不由心生寒意，招架登時散亂。\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "見$N" HIC "攻勢兇猛異常，實非"
                       "尋常，急忙打起精神，小心應付開來。\n" NOR;
        }
        message_combatd(msg, me, target);

        addn("neili", -7*20, me);

        for (i = 0; i < 7; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        me->start_busy(1 + random(7));

        return 1;
}