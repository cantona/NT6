// This program is a part of NITAN MudLIB
// he.c

#include <ansi.h>

inherit F_SSERVER;
string name() { return "合字訣"; }
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("日月鞭法「合」字訣只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");

        if ((int)me->query_skill("riyue-bian", 1) < 135)
                return notify_fail("你的日月鞭法不夠嫻熟，不會使用「合」字訣。\n");

        if( query("neili", me)<350 )
                return notify_fail("你的真氣不夠，無法使用「合」字訣。\n");

        if (me->query_skill_mapped("whip") != "riyue-bian")
                return notify_fail("你沒有激發日月鞭法，無法使用「合」字訣。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "將手中的" + weapon->name() +
              HIY "一抖，使出日月鞭法「合」字訣，舞起漫天鞭影！\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "parry");

        attack_time = 5;
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIC "結果$p" HIC "被$P" HIC
                       "攻了個措手不及，目接不暇，疲於奔命！\n" NOR;
                count = ap / 10;
                addn_temp("apply/attack", count, me);
                attack_time += random(ap / 45);
        } else
        {
                msg += HIC "$n" HIC "見$N" HIC "鞭勢恢弘，心下凜然，凝神應付。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        if (attack_time > 10)
                attack_time = 10;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(2);
        return 1;
}
