// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "耳光式"; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「耳光式」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( (int)me->query_skill("liancheng-jianfa", 1) < 70 )
                return notify_fail("你的連城劍法不夠嫻熟，不會使用。\n");

        if( (int)me->query_skill("force", 1) < 70 )
                return notify_fail("你的基本內功不夠高。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在內力太弱，不能使用「耳光式」。\n");

        msg = HBYEL "只見$N手中兵器由右手快速交換到左手，右手以意想不到的方位揮向$n的臉頰。\n"NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           CYN "$n只覺只覺得臉上一正火辣辣的生痛，"
                                           "已被$N響亮的打了一耳光！\n" NOR);

                addn("neili", -200, me);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p身形一側,躲過了$P的掌風。\n" NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
