#include <ansi.h>
#include <combat.h>

#define JU "「" HIR "赤血爪" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JU "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(JU "只能空手施展。\n");

        if ((int)me->query_skill("yingtuo-luozhua", 1) < 200)
                return notify_fail("你因陀羅爪不夠嫻熟，難以施展" JU "。\n");

        if (me->query_skill_mapped("claw") != "yingtuo-luozhua")
                return notify_fail("你沒有激發因陀羅爪，難以施展" JU "。\n");

        if (me->query_skill_prepared("claw") != "yingtuo-luozhua")
                return notify_fail("你沒有準備因陀羅爪，難以施展" JU "。\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的內功修為不夠，難以施展" JU "。\n");

        if( query("neili", me)<420 )
                return notify_fail("你現在的真氣不夠，難以施展" JU "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap=me->query_skill("claw")+query("force", me);
        dp=target->query_skill("parry")+query("force", target);

        msg = HIW "\n$N" HIW "運轉真氣，雙手忽成爪行，施出絕招「" HIR "赤"
              "血爪" HIW "」，迅猛無比地抓向$n" HIW "。\n" NOR;

        if (ap * 3 / 4 + random(ap) > dp)
        {
                damage = ap + random(ap);
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
                                           HIR "但見$N" HIR "雙爪劃過，$n" HIR "已閃避不及，胸口被$N" HIR
                                           "抓出十條血痕。\n" NOR);

                me->start_busy(2);
                addn("neili", -400, me);
        } else
        {
                msg += CYN "$n" CYN "奮力招架，竟將$N" CYN "這招化解。\n" NOR;

                me->start_busy(2);
                addn("neili", -200, me);
        }
        message_sort(msg, me, target);
        return 1;
}