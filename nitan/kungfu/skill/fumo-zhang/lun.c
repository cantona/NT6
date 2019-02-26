// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "風火輪" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對，難以施展"+name()+"。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，難以施展"+name()+"。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展"+name()+"。\n");

        if ((int)me->query_skill("fumo-zhang", 1) < 120)
                return notify_fail("你二十四路伏魔杖火候不夠，難以施展"+name()+"。\n");

        if (me->query_skill_mapped("staff") != "fumo-zhang")
                return notify_fail("你沒有激發二十四路伏魔杖，難以施展"+name()+"。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "一聲暴喝，手中" + weapon->name() +
              HIW "狂舞，殘影化作無數大圈，宛若" HIR "風火輪"
              HIW "般鋪天蓋地卷向$n" HIW "。\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "staff");

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "完全無法看清招中虛實，只"
                                           "聽「砰砰砰」幾聲，已被$N" HIR "擊中數"
                                           "杖，嘔血連連！\n" NOR);
                me->start_busy(3);
                addn("neili", -150, me);
        } else
        {
                msg += CYN "可是$n" CYN "奮力招架，左閃右避，好不容"
                       "易抵擋住了$N" CYN "的攻擊。\n" NOR;
                me->start_busy(4);
                addn("neili", -80, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
