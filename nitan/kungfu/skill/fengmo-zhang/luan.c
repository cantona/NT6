// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "群魔亂舞" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int lvl;
        int i, ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你所使用的武器不對，難以施展"+name()+"。\n");

        if ((lvl = (int)me->query_skill("fengmo-zhang", 1)) < 120)
                return notify_fail("你瘋魔杖法火候不夠，難以施展"+name()+"。\n");

        if (me->query_skill_mapped("staff") != "fengmo-zhang")
                return notify_fail("你沒有激發瘋魔杖法，難以施展"+name()+"。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，難以施展"+name()+"。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不足，難以施展"+name()+"。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "只見$N" HIR "眼中殺氣大盛，暴喝一聲，飛撲上前，"
                  "便如發狂一般，手中的" + weapon->name() +
              HIR "化出數道殘影，一齊打向$n" HIR "！\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {

                msg += HIY "$n" HIY "見$N" HIY "這等聲勢，早已無心戀"
                       "戰，一時不知應該如何抵擋，唯有連連後退。\n" NOR;
                count = lvl / 10;
                addn_temp("apply/attack", count, me);
        } else
                count = 0;

        message_combatd(msg, me, target);
        addn("neili", -100, me);

        for (i = 0; i < 3; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(5));
        return 1;
}