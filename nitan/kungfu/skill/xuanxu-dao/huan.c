#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "亂環決"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「亂環決」只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功的修為不夠，不能使用亂環決！\n");

        if (me->query_skill("xuanxu-dao", 1) < 135)
                return notify_fail("你的玄虛刀法修為不夠，目前不能使用亂環決！\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真氣不夠，不能使用亂環決！\n");

        msg = HIW "$N" HIW "使出玄虛刀法中的絕技亂環決，刀出成環，環環相連，只絞的$n" + HIW
             "眼前一片影環。\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -180, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "就聽見“喀喀喀”幾聲脆響，$p" HIR "一聲"
                                           "慘叫，全身各處骨頭被刀環一一絞斷，像灘軟泥般"
                                           "塌了下去！\n" NOR );
        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "奮力格擋，$P" CYN
                       "只覺得精力略有衰竭，手中刀光漸緩。 \n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
