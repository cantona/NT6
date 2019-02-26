// moxiao.c 魔笑

#include <ansi.h>

inherit F_SSERVER;

string name() { return "魔笑"; }

int perform(object me, object target)
{
        string msg;
        object weapon;
        int i;
        int skill;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「魔笑」只能對戰鬥中的對手使用。\n");

        skill = me->query_skill("tianmo-jian", 1);

        if (skill < 150)
                return notify_fail("你的天魔劍法修為有限，現在不能使用「魔笑」！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠，無法運用「魔笑」！\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你只有裝備劍才能施展「魔笑」！\n");

        msg = HIR "$N" HIR "突然間身形連轉，口中發出陣陣淒厲的怪笑，$n"
              HIR "只覺耳中有如針刺，不禁心亂神迷，攻勢頓緩。\n$N"
              HIR "驀的撲到$n" HIR "近前，手中的" + weapon->name() +
              HIR "一振，瞬間已向$p刺出數劍。\n" NOR;

        message_combatd(msg, me, target);
        count = skill / 2;
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))  break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(3));
        addn_temp("apply/attack", -count, me);

        return 1;
}
