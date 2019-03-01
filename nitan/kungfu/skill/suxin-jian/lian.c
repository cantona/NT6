#include <ansi.h>

#define LIAN "「" HIW "連環劍術" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;
 
        if( userp(me) && !query("can_perform/suxin-jian/lian", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LIAN "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" LIAN "。\n");

        if ((int)me->query_skill("suxin-jian", 1) < 120)
                return notify_fail("你玉女素心劍不夠嫻熟，難以施展" LIAN "。\n");

        if ((int)me->query_skill("dodge", 1) < 100)
                return notify_fail("你的輕功修為不夠，難以施展" LIAN "。\n");

        if (me->query_skill_mapped("sword") != "suxin-jian")
                return notify_fail("你沒有激發玉女素心劍，難以施展" LIAN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" LIAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIM "\n$N" HIM "身子輕輕一轉，霎時向$n" HIM "劈出了數劍！劍招看"
             "似簡單，但卻迅猛非常，令人匪夷所思！" NOR;

        message_sort(msg, me, target);

        ap = me->query_skill("sword");
        dp = target->query_skill("dodge");

        attack_time = 4;

        if (ap / 2 + random(ap * 2) > dp)
        {
                msg = HIR "結果$n" HIR "被$N" HIR "攻了個措手不及，$n"
                      HIR "慌忙招架，心中叫苦。\n" NOR;
                count = ap / 8;
                attack_time += random(ap / 40);
                addn_temp("apply/attack", count*2, me);
        } else
        {
                msg = HIC "$n" HIC "見$N" HIC "這幾劍招式凌厲，兇猛異"
                      "常，只得苦苦招架。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 20, 20);
        }
        addn_temp("apply/attack", -count*2, me);
        me->start_busy(1 + random(attack_time));

        return 1;
}