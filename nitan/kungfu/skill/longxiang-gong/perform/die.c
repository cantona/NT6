// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return WHT "象跌勢" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp;
        int i, count;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("longxiang-gong", 1) < 240)
                return notify_fail("你的龍象般若功修為不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "longxiang-gong")
                return notify_fail("你沒有激發龍象般若功為拳腳，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("你沒有激發龍象般若功為內功，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "longxiang-gong")
                return notify_fail("你沒有準備使用龍象般若功，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "驀地收回雙掌，施出密宗絕學「" NOR + WHT "象跌勢"
              HIY "」，雙臂再度橫移，猛貫向$n" HIY "！\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_con()*10;
        dp = defense_power(target, "parry") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp)
        {
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIR "$n" HIR "全然無力阻擋，竟被$N"
                                HIR "一拳擊得飛起，重重的跌落在地上。\n" NOR;
                        addn("neili", -50, me);
                        me->start_busy(1);

                        message_combatd(msg, me, target);

                        target->receive_damage("qi", 100, me);
                        set("eff_qi", 1, target);
                        set("eff_jing", 1, target);
                        target->unconcious(me);

                        me->start_busy(1 + random(2));
                        return 1;
                } else
                {
                        count = ap / 10;
                        msg += HIR "$n" HIR "見$P" HIR "來勢迅猛之極，一時不知該如"
                                "何作出抵擋，竟呆立當場。\n" NOR;
                }
        } else
        {
                msg += HIY "$n" HIY "見$p" HIY "來勢迅猛之極，甚難防備，連"
                       "忙振作精神，小心抵擋。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);

        addn("neili", -300, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(3));
        addn_temp("apply/attack", -count, me);

        return 1;
}
