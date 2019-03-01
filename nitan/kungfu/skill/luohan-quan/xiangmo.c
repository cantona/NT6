// This program is a part of NITAN MudLIB
// xiangmo.c 羅漢降魔

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
       
        // if (userp(me) && ! me->query("can_perform/luohan-quan/xiangmo"))
        //        return notify_fail("你還沒有受過高人指點，無法施展「羅漢降魔」。\n");
                
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「羅漢降魔」只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("luohan-quan", 1) < 20)
                return notify_fail("你的羅漢拳法不夠嫻熟，現在還無法使用「羅漢降魔」。\n");
                                
        if( query("neili", me)<50 )
                return notify_fail("你現在真氣不夠，無法運用「羅漢降魔」。\n");
                        
        if (me->query_skill_mapped("cuff") != "luohan-quan") 
                return notify_fail("你沒有激發羅漢拳，無法使用羅漢降魔！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "嗨的一聲，一拳平平朝$n"
              HIY "打出，姿勢有板有眼，頗具風范。\n" NOR;

        ap = attack_power(me, "cuff"); 
        dp = defense_power(target, "parry"); 
        
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "cuff");
                addn("neili", -30, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "只見$n" HIR "一個招架失誤，登時"
                                           "被這拳打了個正著，悶哼一聲，退了一步。\n" NOR);
                me->start_busy(1 + random(2));
        } else 
        {
                msg += CYN "可是$p" CYN "輕輕一格，架住了$P"
                       CYN "的來拳。\n" NOR;
                addn("neili", -10, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
