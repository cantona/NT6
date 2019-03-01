// xiangmo.c 羅漢降魔－－十八羅漢棍

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        
        if (! target) target = offensive_target(me);
    if( userp(me) && !query("can_perform/luohan-gun/xiangmo", me) )
                return notify_fail("你使用的外功中沒有這個功能！\n");
        
        if (! target || ! me->is_fighting(target))
                return notify_fail("「羅漢降魔」只能對戰鬥中的對手使用。\n");

        if (me->query_skill("luohan-gun", 1) < 100) 
        return notify_fail("你的羅漢棍法不夠嫻熟，現在還無法使用「羅漢降魔」。\n");
                                
        if( query("neili", me)<150 )
        return notify_fail("你現在真氣不夠，無法運用「羅漢降魔」。\n");
                
        if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "嗨的一聲，一棍平平朝$n"
              HIY "掃出，招式雖然簡單，但是卻也是力道極重。\n" NOR;

        ap = me->query_skill("club");
        dp = target->query_skill("parry");
        if (ap / 2 + random(ap) > dp)
        {
                damage = 100 + ap / 5 + random(ap / 5);
                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 20,
                                           HIR "只見$n" HIR "一個招架失誤，登時"
                                           "被這棍打了個正著，悶哼一聲，退了一步。\n" NOR);
                me->start_busy(2);
        } else 
        {
                msg += CYN "可是$p" CYN "輕輕一格，架住了$P"
                       CYN "的棍勢。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}