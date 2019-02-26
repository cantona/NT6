// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "天下無狗" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, count;
        int i, attack_time;

        if( query("wugou", me)<500 )
                return notify_fail("你還沒有受過高人指點，無法施展" + name() + "。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill("dagou-bang", 1) < 220)
                return notify_fail("你打狗棒法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("staff") != "dagou-bang")
                return notify_fail("你沒有激發打狗棒法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功火候不足，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "手中" + weapon->name() + HIW "一卷，帶"
              "起陣陣風聲，猶若千百根相似，層層疊疊將$n" HIW "籠罩"
              "其中。\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "parry");

        attack_time = 5;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "只覺眼花繚亂，發現四面八方皆是杖"
                       "影，心底寒意頓生，招架散亂。\n" NOR;
                count = ap / 5;
                addn_temp("apply/attack", count, me);
                addn_temp("apply/damage", count, me);
                attack_time += random(ap / 90);
        } else
        {
                msg += HIY "$n" HIY "只覺眼前一花，發現四面八方皆是杖"
                       "影，急忙收斂心神，仔細招架。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        if (attack_time > 12)
                attack_time = 12;

        addn("neili", -attack_time*30, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(1 + random(4));

        return 1;
}
