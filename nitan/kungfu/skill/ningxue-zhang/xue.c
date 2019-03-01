#include <ansi.h>
#include <combat.h>

#define XUE "「" HIW "繽紛雪舞" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int i, attack_time;

        if( userp(me) && !query("can_perform/ningxue-zhang/xue", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XUE "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你所使用的武器不對，難以施展" XUE "。\n");

        if ((int)me->query_skill("ningxue-zhang", 1) < 50)
                return notify_fail("你的凝雪杖法不夠嫻熟，難以施展" XUE "。\n");

        if (me->query_skill_mapped("staff") != "ningxue-zhang")
                return notify_fail("你沒有激發凝雪杖法，難以施展" XUE "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你目前的真氣不夠，難以施展" XUE "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "\n$N" HIC "驀的一聲清嘯，施出絕學「" HIM "繽紛雪舞"
              HIC "」，手中" + weapon->name() + HIC "呼呼作響。霎時間"
              "連連攻向$n" HIC "。" NOR;

        message_sort(msg, me, target);

        attack_time = 4;

        ap = me->query_skill("sword");
        dp = target->query_skill("dodge");

        attack_time += random(ap / 40);

        if (attack_time > 6)
                attack_time = 6;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(attack_time));

        return 1;
}