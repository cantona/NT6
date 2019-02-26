#include <ansi.h>
#include <combat.h>

#define KAI "「" WHT "五嶽為開" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i;

        if( userp(me) && !query("can_perform/pobei-tui/kai", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(KAI "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用" KAI "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候太淺，難以施展" KAI "。\n");

        if ((lvl = (int)me->query_skill("pobei-tui", 1)) < 100)
                return notify_fail("你的破碑腿不夠嫻熟，難以施展" KAI "。\n");

        if (me->query_skill_mapped("unarmed") != "pobei-tui")
                return notify_fail("你現在沒有激發破碑腿，難以施展" KAI "。\n");

        if (me->query_skill_prepared("unarmed") != "pobei-tui")
                return notify_fail("你現在沒有準備破碑腿，難以施展" KAI "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在真氣太弱，難以施展" KAI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = WHT "只見$N" WHT "身形猛轉，霎那間雙腿流星般連環踢出，足帶風塵，腿影將$n"
              WHT "團團籠罩。\n" NOR;
        addn("neili", -100, me);

        if (random(me->query_skill("force") + me->query_skill("unarmed")) >
            target->query_skill("force"))
        {
                msg += HIR "$n" HIR "見無數腿影向自己襲來，全然分辨"
                       "不清真偽，只得拼命運動抵擋。\n" NOR;
                count = lvl / 5;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "可是$n" HIC "凝神頓氣，奮力抵擋，絲毫不"
                       "受腿影的干擾，。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->start_busy(random(4));
        addn_temp("apply/attack", -count, me);
        return 1;
}
