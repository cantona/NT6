// suolong.c 鎖龍訣

#include <ansi.h>
#include <combat.h>

string name() { return HIW "鎖龍訣" NOR; }

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
            query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對，無法施展" + name() + "。\n");

        if ((int)me->query_skill("ruanhong-zhusuo", 1) < 150)
                return notify_fail("你的軟紅蛛索不夠嫻熟，無法施展" + name() + "。\n");

        if( query("neili", me)<350 )
                return notify_fail("你的真氣不夠，無法施展" + name() + "。\n");

        if (me->query_skill_mapped("whip") != "ruanhong-zhusuo")
                return notify_fail("你沒有激發軟紅蛛索，無法施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "使出「鎖龍」訣，手中" + weapon->name() +
              HIW "一抖，登時幻出漫天鞭影，宛如蛟龍通天，一齊襲向$n"
              HIW "而去！\n\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "parry");
        attack_time = 4;
        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIC "結果$p" HIC "被$P" HIC
                       "攻了個措手不及，目接不暇，疲於奔命！\n" NOR;
                count = ap / 12;
                addn_temp("apply/attack", count, me);
                attack_time += random(ap / 45);
        } else
        {
                msg += HIC "$n" HIC "見$N" HIC "鞭勢恢弘，心下凜然，凝神應付。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*20, me);

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
