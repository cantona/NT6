#include <ansi.h>
#include <combat.h>

#define KONG "「" HIG "破碎虛空" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/pokong-quan/kong", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(KONG "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(KONG "只能空手施展。\n");

        if ((int)me->query_skill("pokong-quan", 1) < 60)
                return notify_fail("你破空拳法不夠嫻熟，難以施展" KONG "。\n");

        if (me->query_skill_mapped("cuff") != "pokong-quan")
                return notify_fail("你沒有激發破空拳法，難以施展" KONG "。\n");

        if (me->query_skill_prepared("cuff") != "pokong-quan")
                return notify_fail("你沒有準備破空拳法，難以施展" KONG "。\n");

        if (me->query_skill("force") < 80)
                return notify_fail("你的內功修為不夠，難以施展" KONG "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" KONG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = me->query_skill("cuff");
        dp = target->query_skill("parry");

        msg = HIC "\n$N" HIC "仰天長嘯，雙拳揮出，施一招「" HIW "破碎虛空"
              HIC "」，拳速極快，破空長響，分襲$n" HIC "面門和胸口。" NOR;
        
        message_sort(msg, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                damage = (int)me->query_skill("henshan-quan", 1);
                damage += random(damage / 2);

                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                          HIR "$N" HIR "出手既快，方位又奇，$n"
                                          HIR "閃避不及，悶哼一聲，已然中拳。\n" NOR);

                addn("neili", -100, me);
                me->start_busy(2 + random(2));                                         
        } else
        {
                msg = CYN "$n" CYN "不慌不忙，以快打快，將$N"
                      CYN "這招化去。\n" NOR;

                addn("neili", -30, me);
                me->start_busy(2 + random(3));
        }
        message_combatd(msg, me, target);
        return 1;
}