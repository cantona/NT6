// heal.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

int exert(object me, object target)
{
  if ( userp(me) && !wizardp(me) && 
  !query("perform/heal", me) && 
  !query("can_perform/baiyun-xinfa/heal", me) && 
  !query_temp("murong/xingyi", me) )
   return notify_fail("你所使用的內功中沒有這種功能。");

        if( me->is_fighting() )
                return notify_fail("戰鬥中運功療傷？找死嗎？\n");

        if( me->is_busy() )
                return notify_fail("你現在正忙著呢，哪有空運功？\n");

        if( (int)me->query_skill("baiyun-xinfa", 1) < 20)
                return notify_fail("你的白雲心法修為還不夠。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的真氣不夠。\n");
/*
        if( query("eff_qi", me) >= query("max_qi", me) )
                return notify_fail(HIR"你沒有受傷，不必運真氣療傷！\n"NOR);
*/
        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("你已經受傷過重，只怕一運真氣便有生命危險！\n");

        write( HIW "你全身放鬆，坐下來運起白雲心法開始療傷。\n" NOR);
        message("vision",
                HIW + me->name() + "坐下運功療傷，頭頂白霧繚繞，半響後吐出一口濁
氣，氣色已恢復正常。\n" NOR, environment(me), me);

        me->receive_curing("qi", 10 + (int)me->query_skill("force")/5 );
        addn("neili", -50, me);
        set("jiali", 0, me);
        me->start_busy(1);

        return 1;
}
int help(object me)
{
        write(WHT"\n白雲心法之自療："NOR"\n");
        write(@HELP

        使用功效：
                為自己療傷

        出手要求：
                白雲心法20級
                內力50
HELP
        );
        return 1;
}