#include <ansi.h>
#include <combat.h>

#define ZHEN "「" WHT "蟾震九天" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int i, count;

        if( userp(me) && !query("can_perform/jiuyin-hamagong/zhen", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(ZHEN "只能空手使用。\n");

        if ((int)me->query_skill("jiuyin-hamagong", 1) < 250)
                return notify_fail("你九陰蛤蟆功火候不夠，難以施展" ZHEN "。\n");
                
        if ((int)me->query_skill("unarmed", 1) < 250)
                return notify_fail("你基本掌法沒練好，難以施展" ZHEN "。\n");        

        if (me->query_skill_mapped("unarmed") != "jiuyin-hamagong")
                return notify_fail("你沒有激發九陰蛤蟆功，難以施展" ZHEN "。\n");

        if (me->query_skill_prepared("unarmed") != "jiuyin-hamagong")
                return notify_fail("你沒有準備九陰蛤蟆功，難以施展" ZHEN "。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的內功修為不夠，難以施展" ZHEN "。\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("你的內力修為不夠，難以施展" ZHEN "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你現在的真氣不足，難以施展" ZHEN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "突然伏地低嘶，心中暗念九陰蛤蟆功心法。口中冒出絲絲白氣，少傾，一股真氣\n"        
                  "由丹田直湧而上，$N隨即猛然躍至半空，使出「 "HIY "蟾震九天" HIY "」，雙掌將全身真氣不停\n"

                  "擊出，剎那間，飛沙走石，煙塵滾滾，勁力有如排山倒海，千軍萬馬般往$n全身轟去。\n" NOR;  

        ap=me->query_skill("unarmed")+query("str", me)*5;
        dp=target->query_skill("parry")+query("str", target)*5;

        if( query("max_neili", me)>query("max_neili", target)*2 )
        { 
                msg += HIY "$n" HIR "全然無力阻擋，竟被$N" 
                       HIY "一拳擊得飛起，重重的跌落在地上。\n" NOR; 
                addn("neili", -50, me);
                me->start_busy(1); 
 
//                message_combatd(msg, me, target); 

   
                target->start_busy(5); 
                set("qi", 1, target);
                set("eff_qi", 1, target);
  
        } else

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "\n$n" HIR "不料$N" HIR "會使出如此功力非同小可且招式詭異招式"
                       "立時招架散亂，連連出招，全身有如撕裂般痛苦，像斷線風箏般彈出丈之遠!\n" NOR;
                count = ap / 6;
        } else
        {
                msg += HIC "$n" HIC "自如此招非同小可，不敢小覷，急忙"
                       "收斂心神，神定氣清，運足全身功力檔住$N" HIC "的掌力。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count, me);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(8) < 3 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn("neili", -600, me);
        me->start_busy(1 + random(8));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count, me);
        return 1;
}
