#include <ansi.h>
#include <combat.h>

#define JU "「" HIM "真龍聚" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/dulong-shenzhua/ju", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JU "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(JU "只能空手施展。\n");

        if ((int)me->query_skill("dulong-shenzhua", 1) < 130)
                return notify_fail("你毒龍神爪功不夠嫻熟，難以施展" JU "。\n");

        if (me->query_skill_mapped("claw") != "dulong-shenzhua")
                return notify_fail("你沒有激發毒龍神爪功，難以施展" JU "。\n");

        if (me->query_skill_prepared("claw") != "dulong-shenzhua")
                return notify_fail("你沒有準備毒龍神爪功，難以施展" JU "。\n");

        if (me->query_skill("force") < 180)
                return notify_fail("你的內功修為不夠，難以施展" JU "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" JU "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        ap=me->query_skill("claw")+query("force", me);
        dp=target->query_skill("parry")+query("force", target);

        msg = HIC "\n$N" HIC "運轉真氣，將體內真氣積聚于雙爪間，猛然間雙爪凌"
              "空而下，猶如神龍般劃向$n" HIC "，這招正是玄冥谷絕學「" HIM "真"
              "龍聚" HIC "」。\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 35,
                                           HIR "但見$N" HIR "雙爪劃過，$n" HIR "已閃避不及，胸口被$N" HIR
                                           "抓出十條血痕。\n" NOR);

                me->start_busy(3);
                addn("neili", -220, me);
        } else
        {
                msg += CYN "$n" CYN "奮力招架，竟將$N" CYN "這招化解。\n" NOR;

                me->start_busy(4);
                addn("neili", -100, me);
        }
        message_sort(msg, me, target);
        return 1;
}