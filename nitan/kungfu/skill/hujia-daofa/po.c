// This program is a part of NITAN MudLIB
// po.c 破字訣

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "破字訣"; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「破字訣」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("運用「破字訣」手中必須有刀！\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 90)
                return notify_fail("你的胡家刀法不夠嫻熟，不會使用「破字訣」。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功修為不夠高。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在內力太弱，不能使用「破字訣」。\n");

        msg = HIM "$N" HIM "手中的" + weapon->name() +
              HIM "輕輕一轉，一股無形刀氣悄然無息的襲向$n" HIM "。\n"NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 65,
                                           HIR "只見$n" HIR "一聲慘叫，整個人如遭"
                                           "電擊，口中鮮血狂噴而出！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "可是$p" HIC "默運內力，硬是抵擋了$P"
                       HIC "的這記無形刀氣。\n"NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}