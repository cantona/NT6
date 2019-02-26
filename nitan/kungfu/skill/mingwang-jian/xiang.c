#include <ansi.h>
#include <combat.h>

string name() { return HIY "降魔" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("mingwang-jian", 1) < 140)
                return notify_fail("你不動明王劍不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "mingwang-jian")
                return notify_fail("你沒有激發不動明王劍，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "縱身躍入半空，將全身勁氣貫於" + weapon->name() +
              HIY "中，劍尖頓時吐出一股劍氣直指$n" HIY "而去。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "只見一道黃芒閃過，微作差"
                                           "異，登時只覺全身一麻，劍氣已透胸而過！"
                                           "\n" NOR);
        } else
        {
                addn("neili", -50, me);
                me->start_busy(3);
                msg += CYN "可是$n" CYN "一聲冷笑，飛身一躍而起，避開"
                       CYN "$N" CYN "發出的劍氣。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
