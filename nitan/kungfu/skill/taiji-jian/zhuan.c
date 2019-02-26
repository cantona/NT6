// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "劍輪嵐轉" NOR; }

inherit F_SSERVER;

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

        if ((int)me->query_skill("taiji-jian", 1) < 160)
                return notify_fail("你的太極劍法不夠嫻熟，難以施展" + name() + "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("你沒有激發太極劍法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "一聲清嘯，手中" + weapon->name() +
              HIW "龍吟不定，化出一個個圓圈，把$n" HIW "圈在當"
              "中。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        attack_time = 5;
        if (ap / 2 + random(ap*4/3) > dp)
        {
                msg += HIY "結果$p" HIY "被$P" HIY
                       "攻了個措手不及，連連後退不暇！\n" NOR;
                count = ap / 10;

                attack_time += random(ap / 45);
        } else
        {
                msg += HIC "$n" HIC "見$N" HIC "這幾劍並無破綻"
                       "，不敢大意，小心應付。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        if (attack_time > 10)
                attack_time = 10;

        addn("neili", -attack_time*20, me);
        addn_temp("apply/attack", count, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));

        return 1;
}
