// qing.c 清思劍

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "清思劍"; }

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「清思劍」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if ((int)me->query_skill("tianyu-qijian", 1) < 70)
                return notify_fail("你的天羽奇劍不夠嫻熟，不會使用。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功實在太差，沒法用「清思劍」。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在內力太弱，不能使用「清思劍」。\n");

        if (me->query_skill_mapped("sword") != "tianyu-qijian")
                return notify_fail("你沒有激發天羽奇劍，沒法用「清思劍」。\n");

        msg = HIG "$N" HIG "手腕輕輕一抖，手中的" + weapon->name() +
              HIG "化作一道彩虹，光華眩目，籠罩了$n" HIG "。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);

                addn("neili", -120, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "只見$N" HIR "劍花聚為一線，穿向$n"
                                           HIR "，$p" HIR "只覺一股熱流穿心而過，"
                                           "喉頭一甜，鮮血狂噴而出！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "猛地向前一躍,跳出了$P"
                       CYN "的攻擊范圍。\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
