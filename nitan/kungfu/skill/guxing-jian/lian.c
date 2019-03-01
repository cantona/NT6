#include <ansi.h>
#include <combat.h>

#define LIAN "「" HIM "九星連珠" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int i, attack_time;

        if( userp(me) && !query("can_perform/guxing-jian/lian", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LIAN "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" LIAN "。\n");

        if ((int)me->query_skill("guxing-jian", 1) < 100)
                return notify_fail("你的孤星劍法不夠嫻熟，難以施展" LIAN "。\n");

        if (me->query_skill_mapped("sword") != "guxing-jian")
                return notify_fail("你沒有激發孤星劍法，難以施展" LIAN "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你目前的真氣不夠，難以施展" LIAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "\n$N" HIW "驀的一聲清嘯，施出絕學「" HIM "九星連珠"
              HIW "」，手中" + weapon->name() + HIW "呼呼作響。霎時間"
              "孤星劍法劍招連綿湧出，此起彼伏，劍氣籠罩$n" HIW "全身。" NOR;

        message_sort(msg, me, target);

        attack_time = 4;

        ap = me->query_skill("sword");
        dp = target->query_skill("dodge");

        attack_time += random(ap / 40);

        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*20, me);

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIY "$n" HIY "見$P" HIY "劍勢洶湧，寒意頓生，竟"
                      "被逼得連連後退，狼狽不已。\n" NOR;
        } else
        {
                msg = HIC "$n" HIC "見$N" HIC "這幾劍來勢迅猛無比，毫"
                      "無破綻，只得小心應付。\n" NOR;
        }

        message_combatd(msg, me, target);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(attack_time));

        return 1;
}