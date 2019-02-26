// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "連環劍術" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("yunv-jian", 1) < 120)
                return notify_fail("你玉女劍法不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("dodge", 1) < 100)
                return notify_fail("你的輕功修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "yunv-jian")
                return notify_fail("你沒有激發玉女劍法，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIM "\n$N" HIM "身子輕輕一轉，霎時向$n" HIM "劈出了數劍！劍招看"
             "似簡單，但卻迅猛非常，令人匪夷所思！" NOR;

        message_combatd(msg, me, target);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        attack_time = 4;

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR "結果$n" HIR "被$N" HIR "攻了個措手不及，$n"
                      HIR "慌忙招架，心中叫苦。\n" NOR;
                count = ap / 8;
                attack_time += random(ap / 40);
                addn_temp("apply/attack", count, me);
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
        me->start_busy(1 + random(3));

        return 1;
}