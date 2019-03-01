// wang.c 望斷秋水

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "望斷秋水"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「望斷秋水」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");

        ap = attack_power(me, "whip");

        if (ap < 180)
                return notify_fail("你的流水鞭法等級不夠, 不能使用「望斷秋水」！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，無法運用「望斷秋水」！\n");

        msg = HIC "$N" HIC "一抖手中的" + weapon->name() + HIC
              "，挽出一朵鞭花，隨即運氣于臂，如氣貫長虹般直向$n" HIC
              "擊出。\n" NOR;

        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp || ! living(target))
        {
                addn("neili", -150, me);
                damage = damage_power(me, "whip");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "見來招兇猛，躲閃不及，登時被擊"
                                           "個正中，不由一陣火辣辣的疼痛！\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -40, me);
                msg += CYN "可是$n" CYN "看清來勢，側身避過$N"
                       CYN "這一招。\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
