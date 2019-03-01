// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "纏絲擒拿" NOR; }

string final(object me, object target, int damage);

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name()+"只能空手施展。\n");

        skill = me->query_skill("chansi-shou", 1);

        if (skill < 120)
                return notify_fail("你纏絲擒拿手等級不夠，難以施展"+name()+"。\n");

        if (me->query_skill_mapped("hand") != "chansi-shou")
                return notify_fail("你沒有激發纏絲擒拿手，難以施展"+name()+"。\n");

        if (me->query_skill_prepared("hand") != "chansi-shou")
                return notify_fail("你沒有準備纏絲擒拿手，難以施展"+name()+"。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在的真氣不夠，難以施展"+name()+"。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "悄然貼近$n" HIW "，施出纏絲擒拿，雙手忽"
              "折忽扭，或抓或甩，直瑣$p" HIW "各處要脈。\n" NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -80, me);
                damage = damage_power(me, "hand");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           (: final, me, target, damage :));
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$n" CYN "的看破了$N"
                       CYN "的招式，巧妙的招架拆解，沒露半點破綻。\n" NOR;
                addn("neili", -20, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        string msg;

        msg = HIR "卻見$n" HIR "奮力抵抗，可終究無法"
              "擺脫$N" HIR "的攻勢，連中數掌，";

        if (random(3) >= 1 && ! target->is_busy())
        {
                target->start_busy(damage / 150);
                msg += "難以反擊。\n" NOR;
        } else
                msg += "鮮血狂噴。\n" NOR;

        return  msg;
}