// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "聚劍訣" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill("tianyu-qijian", 1) < 130)
                return notify_fail("你的天羽奇劍不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill("force", 1) < 180)
                return notify_fail("你的內功火候不足，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        msg = HIR "$N" HIR "手腕輕輕一抖，手中的" + weapon->name() +
              HIR "化作一道彩虹，光華眩目，籠罩了$n" HIR "。\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "只見$N" HIR "劍花聚為一線，穿向$n"
                                           HIR "，$p" HIR "只覺一股熱流穿心而過，"
                                           "喉頭一甜，鮮血狂噴而出！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "猛地向前一躍,跳出了$P"
                       CYN "的攻擊範圍。\n"NOR;
                addn("neili", -80, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
