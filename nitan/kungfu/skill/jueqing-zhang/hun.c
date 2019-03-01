#include <ansi.h>
#include <combat.h>

#define HUN "「" HIM "魂飛魄散" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/jueqing-zhang/hun", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUN "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(HUN "只能空手施展。\n");

        if ((int)me->query_skill("jueqing-zhang", 1) < 140)
                return notify_fail("你絕情掌不夠嫻熟，難以施展" HUN "。\n");

        if (me->query_skill_mapped("strike") != "jueqing-zhang")
                return notify_fail("你沒有激發絕情掌，難以施展" HUN "。\n");

        if (me->query_skill_prepared("strike") != "jueqing-zhang")
                return notify_fail("你沒有準備絕情掌，難以施展" HUN "。\n");

        if (me->query_skill("force") < 180)
                return notify_fail("你的內功修為不夠，難以施展" HUN "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" HUN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = me->query_skill("strike");
        dp = target->query_skill("parry");

        msg = HIC "\n$N" HIC "運轉真氣，將內力注於掌風之中，雙掌猛"
              "然拍向$n" HIC "，掌風凌厲無比，氣勢凌人，直可驚天"
              "地，泣鬼神，正是絕情谷絕學「" HIM "魂飛魄散" HIC "」。"
              "\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = (int)me->query_skill("jueqing-zhang", 1);
                damage += random(damage);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "但見$N" HIR "雙掌拍來，掌風作響，"
                                           "當真氣勢凌人。$n" HIR "頓覺心驚膽戰，"
                                           "毫無招架之力，微遲疑間$N" HIR "這掌"
                                           "已正中$n" HIR "胸口，頓將$p震退數步。"
                                           " \n" NOR);

                me->start_busy(3);
                addn("neili", -200, me);
        } else
        {
                msg += CYN "$n" CYN "見$N" CYN "這掌拍來，內力"
                       "充盈，氣勢凌人，只得奮力向後一縱，才躲"
                       "過這一掌。\n" NOR;

                me->start_busy(4);
                addn("neili", -100, me);
        }
        message_sort(msg, me, target);
        return 1;
}