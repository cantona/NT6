#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "火麒蝕月"; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        int ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「火麒蝕月」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if ((int)me->query_skill("ranmu-daofa", 1) < 180)
                return notify_fail("你的燃木刀法不夠嫻熟，不能使用火麒蝕月。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的內功火候不夠，不能使用火麒蝕月。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為太弱，不能使用火麒蝕月。\n");

        if( query("neili", me)<600 )
                return notify_fail("你現在內力太弱，不能使用火麒蝕月。\n");

        if (me->query_skill_mapped("blade") != "ranmu-daofa")
                return notify_fail("你沒有激發燃木刀法，不能施展火麒蝕月。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "只見$N" HIR "手中" + weapon->name() + HIR "一抖，刀身登時騰起"
                        "滔天烈焰，如浴火麒麟一般席捲$n" HIR "全身！\n"NOR;

        me->start_busy(2 + random(2));
        ap = attack_power(me, "balde");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                if( !target->is_busy() )
                        target->start_busy(2);
                damage = damage_power(me, "blade");
                addn("neili", -400, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           RED "只聞一股焦臭從$n" RED "處傳來，已被"
                                           "$P" RED "這精深奧妙的一"
                                           "刀擊中，鮮血飛濺而出！\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "見$P" CYN "來勢洶洶，不敢抵擋，急忙斜躍避開。\n"NOR;
                addn("neili", -200, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
