#include <ansi.h>
#include <combat.h>

#define HONG "「" HIY "戰神轟天訣" NOR "」"

inherit F_SSERVER;


int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if( userp(me) && !query("can_perform/baihua-cuoquan/hong", me) )
                return notify_fail("你還沒有受到高人指點，還不會使用" HONG "。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HONG "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(HONG "只能空手施展。\n");

        if ((int)me->query_skill("baihua-cuoquan", 1) < 250)
                return notify_fail("你的百花錯拳不夠嫻熟，難以施展" HONG "。\n");

        if ((int)me->query_skill("zhanshen-xinjing", 1) < 250)
                return notify_fail("你的戰神心經修為不夠，難以施展" HONG "。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為不足，難以施展" HONG "。\n");

        if (me->query_skill_mapped("unarmed") != "baihua-cuoquan")
                return notify_fail("你沒有激發百花錯拳，難以施展" HONG "。\n");

        if (me->query_skill_mapped("force") != "zhanshen-xinjing")
                return notify_fail("你沒有激發戰神心經，難以施展" HONG "。\n");

        if (me->query_skill_prepared("unarmed") != "baihua-cuoquan")
                return notify_fail("你沒有準備百花錯拳，難以施展" HONG "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你的真氣不夠，難以施展" HONG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "一聲怒嚎，將戰神心經提運極至，雙拳頓時攜着"
              "雷霆萬鈞之勢猛貫向$n" HIW "。\n" NOR;

        ap=me->query_skill("unarmed")+query("level", me)*20+
             me->query_skill("force") + me->query_skill("martial-cognize", 1);

        dp=target->query_skill("parry")+query("level", target)*20+
             target->query_skill("dodge") + target->query_skill("martial-cognize", 1);

        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        me->start_busy(2);
                        addn("neili", -100, me);
                        msg += HIR "只見$N" HIR "一拳轟至，便將$n" HIR "震得"
                               "心脈俱碎，仰天噴出一口鮮血，軟軟癱倒。\n" NOR
                               "( $n" RED "受傷過重，已經有如風中殘燭，隨時都"
                               "可能斷氣。" NOR ")\n";
                        damage = -1;
                } else
                {
                        me->start_busy(4);
                        addn("neili", -600, me);
                        damage = damage_power(me, "unarmed");
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                                   HIR "結果$p" HIR "閃避不及，$P" HIR "的"
                                                   "拳力掌勁頓時透體而入，口中鮮血狂噴，連"
                                                   "退數步。\n" NOR);
                }
        } else
        {
                me->start_busy(5);
                addn("neili", -300, me);
                msg += CYN "可是$p" CYN "識破了$P"
                       CYN "這一招，斜斜一躍避開。\n" NOR;
        }
        message_combatd(msg, me, target);

        if (damage < 0)
        {
                target->receive_wound("qi", 1, me);
                target->die(me);
        }

        return 1;
}