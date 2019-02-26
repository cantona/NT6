// This program is a part of NITAN MudLIB
// wuchang.c 無常五化

#include <ansi.h>

inherit F_SSERVER;
string name() { return "無常五化"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「無常五化」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("施展「無常五化」時必須拿着一把劍！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠，無法施展「無常五化」！\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，難以施展「無常五化」！\n");

        if ((int)me->query_skill("wuchang-zhang", 1) < 150)
                return notify_fail("你的無常杖法還不到家，無法使用「無常五化」！\n");

        if (me->query_skill_mapped("staff") != "wuchang-zhang")
                return notify_fail("你沒有激發無常杖法，不能使用「無常五化」！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "將手中的" + weapon->name() +
             HIY "一蕩，化作無數杖影掃向$n" HIY "！\n" NOR;
        message_combatd(msg, me, target);

        addn("neili", -100, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(2);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(2);
        return 1;
}
