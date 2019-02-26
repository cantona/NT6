// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "破立勢" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg, wp;
        int ap, dp, damage;

        if (! target ) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("yuan_man", me) )
                return notify_fail("你現在無暇施展" + name() + "。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "hammer" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("hammer") != "riyue-lun")
                return notify_fail("你沒有激發日月輪法，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("你沒有激發龍象般若功，難以施展" + name() + "。\n");

        if ((int)me->query_skill("riyue-lun", 1) < 120)
                return notify_fail("你的日月輪法火候不足，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功火候不足，難以施展" + name() + "。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wp = weapon->name();

        msg = HIY "$N" HIY "單手高舉" + wp + HIY "奮力朝$n" HIY "砸下，氣"
              "浪迭起，全然把$n" HIY "卷在其中！\n" NOR;

        ap = attack_power(me, "hammer") +
             query("str", me)*20;

        dp = defense_power(target, "force") +
             query("con", target)*20;

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -300, me);
                damage = damage_power(me, "hammer");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "被$N" HIR "這強悍無比的"
                                           "內勁衝擊得左搖右晃，接連中招，狂噴鮮"
                                           "血。\n" NOR);
                me->start_busy(2);

        } else
        {
                msg += CYN "卻見$p" CYN "渾不在意，輕輕一閃就躲過了$P"
                       CYN "的兇悍招數。\n"NOR;
                addn("neili", -150, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

