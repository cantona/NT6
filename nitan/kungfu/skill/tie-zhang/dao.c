#include <ansi.h>
#include <combat.h>

string name() { return HIR "五指刀" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int i, count;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("tie-zhang", 1) < 180)
                return notify_fail("你鐵掌掌法火候不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "tie-zhang")
                return notify_fail("你沒有激發鐵掌掌法，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "tie-zhang")
                return notify_fail("你沒有準備鐵掌掌法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 280)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<2800 )
                return notify_fail("你的內力修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = WHT "$N" WHT "身形一展，施出鐵掌絕技「" HIR "五指刀" NOR +
              WHT "」，掌鋒激起層層氣浪，朝$n" WHT "狂劈而去。\n" NOR;

        ap=attack_power(me,"strike")+me->query_str()*10;
        dp=defense_power(target,"parry")+target->query_dex()*10;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "面對$N" HIR "這排山倒海般的攻"
                       "勢，完全無法抵擋，招架散亂，連連退後。\n" NOR;
                count = ap / 10;
        } else
        {
                msg += HIC "$n" HIC "心底微微一驚，心知不妙，急忙"
                       "凝聚心神，竭盡所能化解$N" HIC "數道掌力。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count/2, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn("neili", -250, me);
        me->start_busy(1 + random(2));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count/2, me);
        return 1;
}
