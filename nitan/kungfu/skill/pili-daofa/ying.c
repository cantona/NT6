// ying.c 霹靂刀法「刀影重重」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, zhao;

        if (! target) target = offensive_target(me);


        if (! target || ! me->is_fighting(target))
                 return notify_fail("「刀影重重」只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "blade" )
                 return notify_fail("你使用的武器不對。\n");

        if ((int)me->query_skill("pili-daofa", 1) < 120)
                 return notify_fail("你的霹靂刀法火候不夠，無法施展「刀影重重」。\n");

        if( query("neili", me)<120 )
                return notify_fail("你的真氣不夠，不能使用「刀影重重」。\n");

        msg = HIC "$N" HIC "身法忽變，手中" + weapon->name() + "劃出片片刀影，向$n" + HIC
              "一層層捲去。\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");

        if ( ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIR "只聽$p" HIR "一聲慘叫，"
                      "身上頓時被砍得血肉模糊，鮮血崩流！\n" NOR;
                zhao = 5;
                count = ap / 15;
        } else
        {
                msg += CYN "可是$p" CYN "奮力格擋，將$P" CYN
                       "的攻擊化解。\n" NOR;
                zhao = 0;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);
        for (i = 0; i < zhao; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));

        return 1;
}
