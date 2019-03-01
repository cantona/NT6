#include <ansi.h>
#include <combat.h>

#define FEI "「" HIY "飛龍在天" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int i, count;

        if( userp(me) && !query("can_perform/xianglong-zhang/fei", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(FEI "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(FEI "只能空手使用。\n");

        if ((int)me->query_skill("xianglong-zhang", 1) < 150)
                return notify_fail("你降龍十八掌火候不夠，難以施展" FEI "。\n");

        if (me->query_skill_mapped("strike") != "xianglong-zhang")
                return notify_fail("你沒有激發降龍十八掌，難以施展" FEI "。\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("你沒有準備降龍十八掌，難以施展" FEI "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功修為不夠，難以施展" FEI "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為不夠，難以施展" FEI "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" FEI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "施出降龍十八掌「" HIW "飛龍在天"
              HIY "」，雙掌翻滾，宛如一條神龍攀蜒于九天之上"
              "。\n" NOR;  

        ap=me->query_skill("strike")+query("str", me)*10;
        dp=target->query_skill("parry")+query("dex", target)*10;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "面對$N" HIR "這排山倒海般的攻"
                       "勢，完全無法抵擋，招架散亂，連連退後。\n" NOR;
                count = ap / 10;
        } else
        {
                msg += HIC "$n" HIC "心底微微一驚，心知不妙，急忙"
                       "凝聚心神，竭盡所能化解$N" HIC "數道掌力。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count/3, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn("neili", -300, me);
        me->start_busy(1 + random(6));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count/3, me);
        return 1;
}
