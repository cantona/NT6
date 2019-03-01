// This program is a part of NITAN MudLIB
// jingmo.c 驚魔一指

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "驚魔一指"; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「驚魔一指」只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("yizhi-chan", 1) < 120)
                return notify_fail("你的一指禪還不夠嫻熟，現在還無法使用「驚魔一指」。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功火候不夠，難以施展「驚魔一指」。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，無法運用「驚魔一指」。\n");

        if (me->query_skill_mapped("finger") != "yizhi-chan")
                return notify_fail("你沒有激發一指禪，無法使用驚魔一指！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "大喝一聲，中指按出，一股銳利的殺氣攻向$n"
              HIY "，氣勢恢宏之極！\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                           HIR "只見$p" HIR "躲閃不及，被$P"
                                           HIR "這一指正戳在胸前，不由得連聲"
                                           "慘叫，胸口鮮血直流！\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                msg += CYN "可是$p" CYN "急忙躍開，躲開了$P"
                       CYN "這一指。\n" NOR;
                addn("neili", -60, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}