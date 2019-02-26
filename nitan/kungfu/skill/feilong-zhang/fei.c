#include <ansi.h>
#include <combat.h>

string name() { return HIY "龍飛勢" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, wn;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("feilong-zhang", 1) < 160)
                return notify_fail("你飛龍杖法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("staff") != "feilong-zhang")
                return notify_fail("你沒有激發飛龍杖法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 240)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你的內力修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wn = weapon->name();

        msg = HIW "$N" HIW "嗔目大喝，將全身勁力運於右臂，掌中" + wn +
              HIW "頓時離手射出，朝$n" HIW "飛去！\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "staff");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "只覺一股勁風襲到，閃避"
                                           "不及，那根" + wn + HIR "正好擊中胸口"
                                           "，撞斷數根肋骨。\n" NOR);
                me->start_busy(2);
                addn("neili", -300, me);
        } else
        {
                msg += CYN "$n" CYN "見$N" CYN "氣勢如虹，不敢硬"
                       "接，當即向後橫移數尺，躲閃開來。\n" NOR;
                me->start_busy(3);
                addn("neili", -200, me);
        }

        msg += HIY "只見那根" + wn + HIY "餘勢不盡，又向前飛出數"
               "丈，方才沒入土中。\n" NOR;
        weapon->move(environment(me));

        message_combatd(msg, me, target);
        return 1;
}
