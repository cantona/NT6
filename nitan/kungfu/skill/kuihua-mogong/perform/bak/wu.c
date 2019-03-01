// wu.c 群魔亂舞

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int lvl;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("群魔亂舞只能對戰鬥中的對手使用。\n");
 
        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，無法施展群魔亂舞！\n");

        if ((lvl = me->query_skill("kuihua-mogong", 1)) < 150)
                return notify_fail("你的葵花魔功火候不夠，無法施展群魔亂舞！\n");

        if( weapon=query_temp("weapon", me) )
        {
                if( query("skill_type", weapon) != "sword" && 
                    query("skill_type", weapon) != "pin" )
                        return notify_fail("你手裡拿的不是劍，怎麼施"
                                           "展群魔亂舞？\n");
        } else
        {
                if (me->query_skill_prepared("finger") != "kuihua-mogong")
                        return notify_fail("你並沒有準備使用葵"
                                           "花魔功，如何施展群魔亂舞？\n");
        }

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "默運葵花魔功，身形變得奇快無比，接連向$n"
              HIR "攻出數招！\n" NOR;
        i = 5;
        if (lvl + random(lvl) > (int)target->query_skill("dodge"))
        {
                msg += HIR "$n" HIR "只覺得眼前一花，發現四周都是$N"
                       HIR "的身影，不由暗生懼意，接連後退。\n" NOR;
                count = me->query_skill("kuihua-mogong", 1) / 7;
                addn_temp("apply/attack", count, me);
                i += random(6);
        } else
        {
                msg += CYN "$n" CYN "見$N" CYN "身法好快，哪裡"
                       "敢怠慢，連忙打起精神小心應對。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn("neili", -i*20, me);

        while (i--)
        {
                if (! me->is_fighting(target))
                        break;
                if (i > 5 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(7));
        return 1;
}