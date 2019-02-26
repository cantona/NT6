// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "混沌一陽" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        /*
        if (!SKILLS_D->valid_perform(me, __FILE__))
                return 0;
        */
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail(name() + "只能空手施展。\n");

        if (me->query_skill("jiuyang-shengong", 1) < 180)
                return notify_fail("你的九陽神功還不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "jiuyang-shengong")
                return notify_fail("你現在沒有激發九陽神功為拳腳，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("你現在沒有激發九陽神功為內功，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "jiuyang-shengong")
                return notify_fail("你現在沒有準備使用九陽神功，難以施展" + name() + "。\n");

        if (query("neili", me) < 300)
                return notify_fail("你的內力不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "跨前一步，雙手迴圈，頗得太極之意。掌心頓時閃"
              "出一個氣團，向$n" HIR "電射而去。\n" NOR;

        ap = attack_power(me, "force") + me->query_con();
        dp = defense_power(target, "force") + target->query_con();

        addn("neili", -50, me);

        if (ap / 2 + random(ap) < dp)
        {
                msg += HIY "然而$n" HIY "全力抵擋，終於將$N" HIY
                       "發出的氣團撥開。\n" NOR;
                me->start_busy(3);
        } else
        {
                addn("neili", -200, me);
                me->start_busy(1);
                damage = damage_power(me, "force");
                damage+= query("jiali", me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 150,
                                           HIR "$n" HIR "急忙抽身後退，可是氣團射"
                                           "得更快，只聽$p" HIR "一聲慘叫，鮮血飛"
                                           "濺！\n" NOR);
        }
        message_combatd(msg, me, target);
        return 1;
}
