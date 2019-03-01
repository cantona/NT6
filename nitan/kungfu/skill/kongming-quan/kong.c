// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIG "空空如也" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("kongming-quan", 1) < 150)
                return notify_fail("你的空明拳不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "kongming-quan")
                return notify_fail("你沒有激發空明拳，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "kongming-quan")
                return notify_fail("你沒有準備空明拳，難以施展" + name() + "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在的真氣太弱，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = WHT "$N" WHT "使出空明拳「" HIG "空空如也" NOR + WHT "」，拳勁"
              "虛虛實實，變化莫測，讓$n" WHT "一時難以捕捉。\n" NOR;
        addn("neili", -80, me);

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);

                damage = damage_power(me, "unarmed");
                damage+= query("jiali", me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "無法窺測$N" HIR "拳中奧"
                                           "秘，被這一拳擊中要害，登時嘔出一大口"
                                           "鮮血！\n:內傷@?");
        } else
        {
                me->start_busy(2);
                msg += CYN "可是$p" CYN "識破了$P"
                       CYN "的拳招中的變化，精心應對，並沒有吃虧。\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
