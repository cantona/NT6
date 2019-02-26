#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "劍舞千秋" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("miaojia-jian", 1) < 160)
                return notify_fail("你苗家劍法不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 220 )
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<1800 )
                return notify_fail("你的內力修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "miaojia-jian")
                return notify_fail("你沒有激發苗家劍法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "手中" + weapon->name() + HIY "一聲龍吟，三十七勢苗"
              "家劍連環施出，將$n" HIY "罩在劍光之中。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        attack_time = 5;
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$p" HIR "只見得劍光萬道，頓時被$P" HIR
                       "凌厲的劍招攻得應接不暇，連連後退！\n" NOR;
                count = ap / 10;
                addn_temp("apply/attack", count, me);
                addn_temp("apply/damage", count, me);
                attack_time += random(ap / 200);
        } else
        {
                msg += HIC "$n" HIC "見$N" HIC "劍勢洶湧，霍霍劍光"
                       "逼人而來，不敢大意，小心應付。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*25, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(1 + random(3));

        return 1;
}