#include <ansi.h>
#include <combat.h>


#define DING "「" HIY "背心釘" NOR "」"

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if( userp(me) && !query("can_perform/bagua-zhang/ding", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DING "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(DING "只能空手施展。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功修為不夠，難以施展" DING "。\n");

        if ((int)me->query_skill("bagua-zhang", 1) < 80)
                return notify_fail("你的八卦掌不夠嫻熟，難以施展" DING "。\n");

        if (me->query_skill_mapped("strike") != "bagua-zhang") 
                return notify_fail("你沒有激發八卦掌，難以施展" DING "。\n");

        if (me->query_skill_prepared("strike") != "bagua-zhang") 
                return notify_fail("你沒有準備八卦掌，難以施展" DING "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，難以施展" DING "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "身形一轉，已飄至$n" HIY "身後，陡然施出一招「背心"
              "釘」，單手作錐，直插$n" HIY "背心要穴！\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
        
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "strike");
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "結果$p" HIR "閃避不及，被$P" HIR
                                           "這招插中，掌勁頓時透胸而過，口噴鮮血"
                                           "，幾乎摔倒！\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -50, me);
                msg += CYN "可是$p" CYN "識破了$P"
                       CYN "這一招，斜斜一躍避開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}