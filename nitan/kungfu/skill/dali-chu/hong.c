#include <ansi.h>
#include <combat.h>

#define HONG "「" HIY "轟雷萬鈞" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg, wp;
        int ap, dp, damage;

        if( userp(me) && !query("can_perform/dali-chu/hong", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target ) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HONG "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "hammer" )
                return notify_fail("你所使用的武器不對，難以施展" HONG "。\n");

        if (me->query_skill_mapped("hammer") != "dali-chu")
                return notify_fail("你沒有激發無上大力杵，難以施展" HONG "。\n");

        if ((int)me->query_skill("dali-chu", 1) < 80)
                return notify_fail("你無上大力杵火候不足，難以施展" HONG "。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不足，難以施展" HONG "。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為不足，難以施展" HONG "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不足，難以施展" HONG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        wp = weapon->name();

        msg = HIR "$N" HIR "舞動手中" + wp + HIR "，一招「" HIY "轟雷萬鈞"
              HIR "」挾著震天撞擊之聲朝$n" HIR "當頭砸下！\n" NOR;

        ap = me->query_skill("hammer");
        dp = target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -150, me);
                damage = ap / 3 + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "見$N" HIR "來勢洶湧，心"
                                           "知不妙，可已然不及躲避，被這錘擊中胸"
                                           "口，吐血連連。\n" NOR);
                me->start_busy(3);

        } else
        {
                msg += CYN "可是$p" CYN "早知$P"
                       CYN "有此一著，當即巧妙招架，格擋開來。\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}