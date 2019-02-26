#include <ansi.h>
#include <combat.h>

#define QIAN "「" HIW "蛇影萬道" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;
        /*
        if( userp(me) && !query("can_perform/jinshe-jian/wan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");
        */
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(QIAN "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" QIAN "。\n");

        if ((int)me->query_skill("jinshe-jian", 1) < 180)
                return notify_fail("你的金蛇劍法不夠嫻熟，難以施展" QIAN "。\n");

        if( query("neili", me)<260 )
                return notify_fail("你的真氣不夠，難以施展" QIAN "。\n");

        if (me->query_skill_mapped("sword") != "jinshe-jian")
                return notify_fail("你沒有激發金蛇劍法，難以施展" QIAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "\n$N" HIW "一聲長吟，手中" + weapon->name() + HIW "頓時化做無數條靈蛇，"
              "從四面八方同時向$n" HIW "襲去。\n" NOR;

        message_sort(msg, me, target);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        attack_time = 4;

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR "結果$n" HIR "被$N" HIR "攻了個措手不及，$n"
                      HIR "慌忙招架，心中叫苦。\n" NOR;

                count = ap / 5;
                attack_time += random(ap / 35);
        } else
        {
                msg = HIC "$n" HIC "見$N" HIC "這幾劍招式凌厲，詭異"
                      "無比，只得苦苦招架。\n" NOR;
                count = 0;
        }
            message_combatd(msg, me, target);

        if (attack_time > 9)
                attack_time = 9;

        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count/2, me);
        addn("neili", -attack_time*30, me);
        me->start_busy(1 + random(attack_time / 2));

        set_temp("jinshe-jian/lian", 1, me);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                       break;

                if (! target->is_busy() && random(3) == 1)
                       target->start_busy(1);
 
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        delete_temp("jinshe-jian/lian", me);

        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count/2, me);
        return 1;
}