// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "絕命一踢" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp, pp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name()+"只能空手施展。\n");

        if (me->query_skill("jueming-tui", 1) < 80)
                return notify_fail("你絕命腿法不夠嫻熟，難以施展"+name()+"。\n");

        if (me->query_skill_mapped("unarmed") != "jueming-tui")
                return notify_fail("你沒有激發絕命腿法，難以施展"+name()+"。\n");

        if (me->query_skill_prepared("unarmed") != "jueming-tui")
                return notify_fail("你沒有準備絕命腿法，難以施展"+name()+"。\n");

        if( query("neili", me)<200 )
                return notify_fail("你目前的內力不夠，難以施展"+name()+"。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        switch (random(3))
        {
        case 0:
                msg = HIR "只聽$N" HIR "一聲冷哼，側身飛踢，右腿橫"
                      "掃向$n" HIR "，當真是力不可擋。\n" NOR;
                break;

        case 1:
                msg = HIR "$N" HIR "驀地大喝一聲，單腿猛踢而出，直"
                      "踹$n" HIR "腰際，招式極為迅猛。\n" NOR;
                break;

        default:
                msg = HIR "突然只見$N" HIR "雙腿連環踢出，挾著□□"
                      "風聲，以千鈞之勢掃向$n" HIR "。\n" NOR;
                break;
        }

        ap = attack_power(me, "unarmed") + me->query_str();
        dp = defense_power(target, "dodge") + target->query_dex();
        pp = defense_power(target, "parry") + target->query_str();

        if (ap / 2 + random(ap) < pp)
        {
                msg += HIC "可是$n" HIC "身子一晃，硬生生架住了$N"
                       HIC "這一腿。\n" NOR;
                me->start_busy(3);
                addn("neili", -30, me);
        } else
        if (ap / 2 + random(ap) < dp)
        {
                msg += CYN "卻見$n" CYN "鎮定的向後一縱，閃開了$N"
                       CYN "這一腿。\n" NOR;
                me->start_busy(3);
                addn("neili", -30, me);
        } else
        {
                damage = damage_power(me, "unarmed");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "連忙格擋，卻只覺得力道大"
                                           "得出奇，登時被一腳踢得飛起。\n" NOR);
                me->start_busy(2);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);
        return 1;
}
