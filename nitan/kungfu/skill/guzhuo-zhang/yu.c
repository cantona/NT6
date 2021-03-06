#include <ansi.h>
#include <combat.h>

#define YU "「" HIR "大智若愚" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/guzhuo-zhang/yu", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(YU "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(YU "只能空手使用。\n");

        if ((int)me->query_skill("force") < 260)
                return notify_fail("你內功修為不夠，難以施展" YU "。\n");

        if( query("max_neili", me)<2800 )
                return notify_fail("你內力修為不夠，難以施展" YU "。\n");

        if ((int)me->query_skill("guzhuo-zhang", 1) < 180)
                return notify_fail("你古拙掌法火候不夠，難以施展" YU "。\n");

        if (me->query_skill_mapped("strike") != "guzhuo-zhang")
                return notify_fail("你沒有激發古拙掌法，難以施展" YU "。\n");

        if (me->query_skill_prepared("strike") != "guzhuo-zhang")
                return notify_fail("你沒有準備古拙掌法，難以施展" YU "。\n");

        if( query("neili", me)<600 )
                return notify_fail("你現在真氣不夠，難以施展" YU "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "體內真氣迸發，大喝一聲，雙掌向$n" HIR "平平推"
              "去，招數樸實無華，毫無半點花巧可言。\n" NOR;  

        ap=me->query_skill("strike")+query("int", me)*10;
        dp=target->query_skill("force")+query("int", target)*10;

        me->start_busy(3);

        if (ap / 2 + random(ap) > dp)
        { 
                damage = ap + random(ap / 2);
                addn("neili", -300, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "$n" HIR "勘破不透掌中虛實，$N" HIR
                                           "雙掌正中$p" HIR "前胸，“喀嚓喀嚓”接"
                                           "連斷了數根肋骨。\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "見$N" CYN "這掌來勢非凡，不敢"
                       "輕易招架，當即飛身縱躍閃開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
