#include <ansi.h>
#include <combat.h>

#define BEI "「" HIW "萬裡鯨濤大悲神訣" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int i, ap, dp;
        object weapon;
        /*
        if( userp(me) && !query("can_perform/dabei-zhang/bei", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");
        */
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(BEI "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(BEI "只能空手使用。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你內功修為不夠，難以施展" BEI "。\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("你內力修為不夠，難以施展" BEI "。\n");

        if ((int)me->query_skill("dabei-zhang", 1) < 220)
                return notify_fail("你大悲神掌火候不夠，難以施展" BEI "。\n");

        if (me->query_skill_mapped("strike") != "dabei-zhang")
                return notify_fail("你沒有激發大悲神掌，難以施展" BEI "。\n");

        if (me->query_skill_prepared("strike") != "dabei-zhang")
                return notify_fail("你沒有準備大悲神掌，難以施展" BEI "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在真氣不夠，難以施展" BEI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "凄然一聲長嘯，施出「" HIG "萬裡鯨濤大悲神訣"
              HIW "」，雙掌翻滾出漫天掌影，盡數拍向$n" HIW "。\n" NOR;  

        ap = attack_power(me, "strike") + me->query_int();

        dp = defense_power(target, "force") + target->query_int();

        if (ap / 2 + random(ap) > dp)
        { 
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                           HIR "$n" HIR "勘破不透掌中虛實，$N" HIR
                                           "雙掌正中$p" HIR "前胸，“喀嚓喀嚓”接"
                                           "連斷了數根肋骨。\n" NOR);
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "$n" CYN "見$N" CYN "這掌來勢非凡，不敢"
                       "輕易招架，當即飛身縱躍閃開。\n" NOR;
                message_combatd(msg, me, target);
        }

        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn("neili", -300, me);
        me->start_busy(4 + random(3));
        return 1;
}
