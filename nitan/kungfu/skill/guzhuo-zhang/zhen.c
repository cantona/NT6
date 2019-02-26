#include <ansi.h>
#include <combat.h>

#define ZHEN "「" HIW "反璞歸真" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int i, ap, dp;
        object weapon;

        if( userp(me) && !query("can_perform/guzhuo-zhang/zhen", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(ZHEN "只能空手使用。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你內功修為不夠，難以施展" ZHEN "。\n");

        if( query("max_neili", me)<3600 )
                return notify_fail("你內力修為不夠，難以施展" ZHEN "。\n");

        if ((int)me->query_skill("guzhuo-zhang", 1) < 220)
                return notify_fail("你古拙掌法火候不夠，難以施展" ZHEN "。\n");

        if (me->query_skill_mapped("strike") != "guzhuo-zhang")
                return notify_fail("你沒有激發古拙掌法，難以施展" ZHEN "。\n");

        if (me->query_skill_prepared("strike") != "guzhuo-zhang")
                return notify_fail("你沒有準備古拙掌法，難以施展" ZHEN "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在真氣不夠，難以施展" ZHEN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "陡然間$N" HIW "施出「" HIY "璞" HIW "」字訣，雙掌向$n"
              HIW "平平推去，招數樸實無華，毫無半點花巧可言。\n" NOR;  

        ap=me->query_skill("strike")+query("int", me)*8;
        dp=target->query_skill("force")+query("int", target)*8;

        if (ap / 2 + random(ap) > dp)
        { 
                damage = ap + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "$n" HIR "勘破不透掌中虛實，$N" HIR
                                           "雙掌正中$p" HIR "前胸，“喀嚓喀嚓”接"
                                           "連斷了數根肋骨。\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "見$N" CYN "這掌來勢非凡，不敢"
                       "輕易招架，當即飛身縱躍閃開。\n" NOR;
        }

        msg += HIW "\n緊接着$N" HIW "變招「" HIY "真" HIW "」字訣，霎"
               "時只見$N" HIW "雙掌紛飛，化出漫天掌影籠罩$n" HIW "四面"
               "八方。\n"NOR;
        message_combatd(msg, me, target);


        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn("neili", -400, me);
        me->start_busy(4 + random(3));
        return 1;
}
