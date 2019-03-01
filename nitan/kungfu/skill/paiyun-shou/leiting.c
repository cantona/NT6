// This program is a part of NITAN MudLIB
// leiting.c  排雲推手「雷霆一擊」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "雷霆一擊"; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「雷霆一擊」只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("paiyun-shou", 1) < 100)
                return notify_fail("你的排雲推手不夠嫻熟，不會使用「雷霆一擊」。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用「雷霆一擊」！\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，無法使用「雷霆一擊」。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在內力不夠，無法使用「雷霆一擊」。\n");

        msg = HIG "$N" HIG "將真氣凝于雙掌，一聲怒喝，雙臂猛然發勁，向$n" HIG "推出。\n" NOR;

        ap = attack_power(me, "hand") +
             me->query_str()*20;

        dp = defense_power(target, "parry") +
             target->query_str()*20;

        addn("neili", -150, me);

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                damage = damage_power(me, "hand");

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "閃避不及，正中前胸，"
                                           HIR "只聽“□”的一聲，$n"
                                           HIR "狂吐一口鮮血，身子如紙鶴般向後飛出。\n" NOR);
                me->start_busy(2);
        } else
        {       msg += HIC "可是$p" HIC "早有防備，" HIC
                       "急退一步，避開了$P" HIC "這一擊。\n"NOR;
                me->start_busy(2);
        }
        message_vision(msg, me, target);
        return 1;
}
