// This program is a part of NITAN MudLIB
// wuji.c 橫行無忌

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "橫行無忌"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「橫行無忌」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("運用「橫行無忌」必須手中持杖！\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，難以運用使用「橫行無忌」！\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，無法使用「橫行無忌」！\n");

        if ((int)me->query_skill("lingshe-zhangfa", 1) < 150)
                return notify_fail("你的靈蛇杖法還不到家，無法使用「橫行無忌」！\n");

        if (me->query_skill_mapped("staff") != "lingshe-zhangfa")
                return notify_fail("你沒有激發靈蛇杖法，無法使用「橫行無忌」！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "一聲冷笑，手中的" + weapon->name() + HIY "忽然變得"
              "如同活物一般，時上時下，忽左忽右，不知攻向$n" HIY "何處！\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "staff");
                addn("neili", -200, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "實在無法捕做到$P"
                                           HIR "的實招，接連擋空，連中數招，"
                                           "登時吐了一口鮮血！\n" NOR);
                me->start_busy(2);
                if (! target->is_busy())
                target->start_busy(1);
        } else
        {
                msg += CYN "$n" CYN "奮力招架，總算抵擋住了$P"
                       CYN "的攻擊！\n" NOR;
                addn("neili", -80, me);
                me->start_busy(3);
                if (! target->is_busy())
                target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}
