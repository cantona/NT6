// This program is a part of NITAN MudLIB
// xiang.c 

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i;
        
        if( userp(me) && !query("can_perform/jingang-chu/xiang", me) )
                return notify_fail("你還沒有受過高人指點，無法施展鎮魂舞。\n");
                 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「鎮魂舞」只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "staff" )
                return notify_fail("手中杖還使什麼「鎮魂舞」！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠！\n");

        if ((int)me->query_skill("staff") < 100)
                return notify_fail("你的基本杖法火候不夠！\n");

        if ((int)me->query_skill("jingang-chu", 1) < 100)
                return notify_fail("你的胡金剛鎮魂舞杵還不到家，無法使用「鎮魂舞」！\n");

        if (me->query_skill_mapped("staff") != "jingang-chu")
                return notify_fail("你沒有激發金剛鎮魂舞杵，無法使用「鎮魂舞」！\n");

        msg = HIW "$N" HIW "施展出鎮魂舞杵的精妙招式「鎮魂舞」，只見" + weapon->name() +
              HIW "吞吞吐吐，變化莫測，籠罩了$n" HIW "周身要害！\n" NOR;


        message_combatd(msg, me, target);
        
        count = me->query_skill("jingang-chu", 1) / 10;
        
        addn("neili", -150, me);
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));
        return 1;
}

