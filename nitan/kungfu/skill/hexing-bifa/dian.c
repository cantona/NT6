#include <ansi.h>
#include <combat.h>

#define DIAN "「" HIM "內點乾坤" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int i, attack_time;

        if( userp(me) && !query("can_perform/hexing-bifa/dian", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DIAN "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "dagger" )
                return notify_fail("你所使用的武器不對，難以施展" DIAN "。\n");

        if ((int)me->query_skill("hexing-bifa", 1) < 100)
                return notify_fail("你的鶴形筆法不夠嫻熟，難以施展" DIAN "。\n");

        if (me->query_skill_mapped("dagger") != "hexing-bifa")
                return notify_fail("你沒有激發鶴形筆法，難以施展" DIAN "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你目前的真氣不夠，難以施展" DIAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "\n$N" HIW "身法陡快，手中" + weapon->name() + HIW "一揚，"
              "施出絕招「" HIM "內點乾坤" HIW "」，猛然間，" + weapon->name() + HIW
              "連連點向$n" HIW "周身要穴。" NOR;

        message_sort(msg, me, target);

        attack_time = 4;

        ap = me->query_skill("sword");
        dp = target->query_skill("dodge");

        attack_time += random(ap / 40);

        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*30, me);


        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (! target->is_busy() && random(3) == 1)
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(attack_time));

        return 1;
}