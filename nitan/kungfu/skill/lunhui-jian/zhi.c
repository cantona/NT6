#include <ansi.h> 

#define CHAN "「" HIR "神劍指穴" NOR "」" 

inherit F_SSERVER; 

int perform(object me, object target) 
{ 
        object weapon; 
        string msg; 

        if( userp(me) && !query("can_perform/lunhui-jian/zhi", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) 
        { 
                me->clean_up_enemy(); 
                target = me->select_opponent(); 
        }

        if (! target || ! me->is_fighting(target)) 
                return notify_fail(CHAN "只能對戰鬥中的對手使用。\n"); 

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" CHAN "。\n"); 

        if (target->is_busy()) 
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n"); 

        if ((int)me->query_skill("force") < 180) 
                return notify_fail("你的內功火候不夠，難以施展" CHAN "。\n"); 

        if ((int)me->query_skill("lunhui-jian", 1) < 120) 
                return notify_fail("你的釋迦輪回劍還不到家，難以施展" CHAN "。\n"); 

        if (me->query_skill_mapped("sword") != "lunhui-jian") 
                return notify_fail("你沒有激發釋迦輪回劍，難以施展" CHAN "。\n"); 

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠，難以施展" CHAN "。\n"); 

        if (! living(target)) 
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n"); 

        msg = HIY "$N" HIY "內息澎湃，手中" + weapon->name() + HIY "遙遙指向$n，" 
              "一股勁氣自"+ weapon->name() + HIY "上激射而出，直指向$n的周身大穴。\n" NOR; 
        
        if (random(me->query_skill("sword")) > target->query_skill("parry") / 2) 
        {
                msg += HIR "$n" HIR "稍不留神，身上幾處要穴已被內力透過"
                       "，一時間無法動彈。\n" NOR; 
                target->start_busy((int)me->query_skill("lunhui-jian") / 20 + 1); 
                addn("neili", -60, me);
                me->start_busy(1); 
        } else 
        {
                msg += CYN "可是$n" CYN "小心應對，絲毫不亂，縱身" 
                       "躍出了$N" CYN "縱橫劍氣的包圍。\n" NOR; 
                addn("neili", -30, me);
                me->start_busy(2); 
        }
        message_combatd(msg, me, target); 

        return 1; 
}
