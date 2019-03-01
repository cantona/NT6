// heal.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

int exert(object me, object target)
{
  if ( userp(me) && !wizardp(me) && 
  !query("perform/heal", me) && 
  !query("can_perform/dulong-dafa/heal", me) && 
  !query_temp("murong/xingyi", me) )
   return notify_fail("你所使用的內功中沒有這種功能。");
        if( me->is_fighting() )
                return notify_fail("戰鬥中運功療傷？找死嗎？\n");
        if( me->is_busy() )
                return notify_fail("你現在正忙著呢，哪有空運功？\n");
        if( (int)me->query_skill("dulong-dafa", 1) < 20)
                return notify_fail("你的毒龍大法修為還不夠。\n");
        if( query("neili", me)<50 )
                return notify_fail("你的真氣不夠。\n");
/*
        if( query("eff_qi", me) >= query("max_qi", me) )
                return notify_fail(HIR"你沒有受傷，不必運真氣療傷！\n"NOR);
*/
        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("你已經受傷過重，只怕一運真氣便有生命危險！\n");

        write( HIW "你全身放鬆，坐下來開始運功療傷。\n" NOR);
        message("vision", HIW + me->name() + "吐出一口瘀血，臉色看起來好多了。\n" NOR, environment(me), me);

        me->receive_curing("qi", 10 + (int)me->query_skill("force")/5 );
        addn("neili", -50, me);
        set("jiali", 0, me);
        me->start_busy(1);

        return 1;
}
int help(object me)
{
        write(WHT"\n毒龍大法之自療："NOR"\n");
        write(@HELP

        使用功效：
                為自己療傷

        出手要求：
                毒龍大法20級
                內力50
HELP
        );
        return 1;
}
