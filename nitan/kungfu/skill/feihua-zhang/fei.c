#include <ansi.h>
#include <combat.h>

#define FEI "「" HIG "掌打飛花" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int attack_time, i;

        if( userp(me) && !query("can_perform/feihua-zhang/fei", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(FEI "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(FEI "只能空手施展。\n");

        if ((int)me->query_skill("feihua-zhang", 1) < 40)
                return notify_fail("你飛花掌法不夠嫻熟，難以施展" FEI "。\n");

        if (me->query_skill_mapped("strike") != "feihua-zhang")
                return notify_fail("你沒有激發飛花掌法，難以施展" FEI "。\n");

        if (me->query_skill_prepared("strike") != "feihua-zhang")
                return notify_fail("你沒有準備飛花掌法，難以施展" FEI "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在的真氣不夠，難以施展" FEI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = me->query_skill("strike");
        dp = target->query_skill("parry");

        msg = HIC "\n$N" HIC "雙掌陡然連續拍出，剛中帶柔，一招"
              "「" HIG "掌打飛花" HIC "」，雙掌帶風，已將$n" 
              HIC "籠罩在掌風之中。\n" NOR;
        message_sort(msg, me, target);

        if (random(ap) > dp / 2)
        {
                msg = HIR "結果$n" HIR "目不暇接，頓時被$N" HIR "掌"
                      "風所困，頓時陣腳大亂。\n" NOR;
                addn_temp("apply/attack", 10, me);
        } else
        {
                msg = HIY "$n" HIY "看清$N" HIY "這幾招的來路，但"
                      "內勁所至，剛柔並濟，也只得小心抵擋。\n" NOR;          
        }
        message_vision(msg, me, target);

        attack_time += 3 + random(ap / 40);

        if (attack_time > 6)
                attack_time = 6;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (! target->is_busy() && random(3) == 1) 
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->start_busy(1 + random(attack_time));
        addn_temp("apply/attack", -10, me);

        return 1;
}