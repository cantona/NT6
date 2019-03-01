#include <ansi.h>
#include <combat.h>

#define LIAN "「" HIW "奪命連環" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i;

        if( userp(me) && !query("can_perform/lianhuan-mizongtui/lian", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LIAN "只能對戰鬥中的對手使用。\n");

        if ((lvl = (int)me->query_skill("lianhuan-mizongtui", 1)) < 120)
                return notify_fail("你的連環迷蹤腿不夠嫻熟，難以施展" LIAN "。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(LIAN "只能空手施展。\n");
                
        if( query("max_neili", me)<1800 )
                return notify_fail("你的內力的修為不夠，現在無法使用" LIAN "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，難以施展" LIAN "。\n");

        if ((int)me->query_skill("dodge") < 150)
                return notify_fail("你的輕功火候不夠，難以施展" LIAN "。\n");

        if (me->query_skill_prepared("unarmed") != "lianhuan-mizongtui")
                return notify_fail("你現在沒有準備使用連環迷蹤腿，難以施展" LIAN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣太弱，難以施展" LIAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "陡見$N" HIW "全身飛速旋轉，雙腿忽前忽後，接連貫出數腿，流星般疾射$n"
              HIW "胸口。\n" NOR;

        addn("neili", -150, me);

        if (random(me->query_skill("dodge") + me->query_skill("unarmed")) >
            target->query_skill("parry"))
        {
                msg += HIR "$n" HIR "頓時覺得眼花繚亂，無數條腿"
                       "向自己奔來，只得拼命運動抵擋。\n" NOR;
                count = lvl / 5;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "可是$n" HIC "凝神頓氣，奮力抵擋，絲"
                       "毫不受腿影的幹擾，。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->start_busy(random(5));
        addn_temp("apply/attack", -count, me);
        return 1;
}
