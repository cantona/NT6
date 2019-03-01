#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        object weapon=query_temp("weapon", me);

        if( !wizardp(me) && !query("can_perform/dacheng-fosuo/canrao", me) )
                return notify_fail("你所使用的外功中沒有這個功能！\n");
        
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("纏繞訣只能對戰鬥中的對手使用。\n");

        if(me->query_skill("dacheng-fosuo",1) < 150)
                return notify_fail("你的大乘佛索還不夠嫻熟，不會使用纏繞訣。\n");

        if( !weapon 
         || query("skill_type", weapon) != "whip"
        ||      me->query_skill_mapped("whip") != "dacheng-fosuo" ) 
                return notify_fail("你現在無法使用纏繞訣。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠。\n");

        if( target->is_busy() )
        return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

          me->start_perform( 5, "纏繞訣");
    msg = HIG "$N使出纏繞訣，鞭子一揮向$n的雙腿卷去！\n";

        me->start_busy(random(2));
        if( (random(query("combat_exp", me))>query("combat_exp", target)/2 )
                ||      (random(me->query_dex()) > target->query_dex()/2))
        {
        msg += HIY "結果$p被$P一卷，兩條腿被結結實實的捆起來，在地上無法爬起。\n" NOR;
                target->start_busy((int)me->query_skill("dacheng-fosuo",1)/20);
        } 
        else {
                msg += HIW "可是$p看破了$P的纏繞訣，身子一躍便躲開了。\n" NOR;
                me->start_busy(2);
        }
        message_vision(msg, me, target);
        
        addn("jingli", -20, me);
        addn("neili", -200, me);
        return 1;
}

