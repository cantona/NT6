// This program is a part of NITAN MudLIB
// xian.c 神龍初現

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "神龍初現"; }

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("神龍初現只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("shenlong-bashi", 1) < 100)
                return notify_fail("你的神龍八式手法還不夠嫻熟，不能使用神龍初現。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候不夠，不能使用神龍初現。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在真氣不夠，不能使用神龍初現。\n");

        if (me->query_skill_mapped("hand") != "shenlong-bashi")
                return notify_fail("你沒有激發神龍八式手法，不能使用神龍初現。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIG "$N" HIG "腳下輕浮，踉踉蹌蹌，似倒非倒，跌跌撞撞的沖向$n"
              HIG "，同時伸手就是一招，詭秘之極。\n" NOR;

        me->start_busy(2);
        ap = attack_power(me, "hand");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "hand");

                if( !target->is_busy() )
                        target->start_busy(1);
                addn("neili", -125, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "$p" HIR "左遮右擋，卻沒能擋住$P" HIR "這看似無賴"
                                           "的招數，結果被$P" HIR "重重的擊中，哇的吐了一口鮮血。\n" NOR);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企圖，巧妙的擋住了$P"
                       CYN "的進攻。\n" NOR;
                addn("neili", -30, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

