// 蛤蟆功吸毒
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

int exert(object me,object target)
{
        int con1, con2, con3, con;
        con1 = target->query_condition("snake_poison");
//        con2 = target->query_condition("scorpion_poison");
        con3 = target->query_condition("xx_poison");

  if ( userp(me) && !wizardp(me) && 
  !query("perform/xidu", me) && 
  !query("can_perform/hamagong/xidu", me) && 
  !query_temp("murong/xingyi", me) )
   return notify_fail("你所使用的內功中沒有這種功能。");


        if ( !living(target) || target == me )
                return notify_fail("你要為誰吸毒？\n");
                
        notify_fail("不是你要抓的人，湊什麼熱鬧！\n");
        if (!userp(target) && !target->accept_hit(me)) return 0;

        if ( !con1 && !con3 )
                return notify_fail("對方沒有中毒！\n");

        if ( target->is_fighting() )
                return notify_fail("戰鬥中無法運功吸毒！\n");
                
        if( me->is_fighting() )
                return notify_fail("戰鬥中運功吸毒？找死嗎？\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠。\n");

        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("你已經受傷過重，只怕一運真氣便有生命危險！\n");

        if ((int)me->query_skill("hamagong", 1) < 50)
                return notify_fail("你的蛤蟆功修為還不夠。\n");

        if ((int)me->query_skill("xidu-poison", 1) < 50)
                return notify_fail("你的西毒毒技修為還不夠。\n");

        if ( con1 > 0 ) {
                if( query("neili", me)<100 )
                        return notify_fail("你的真氣不夠。\n");
                con = ( ( me->query_skill("hamagong", 1) / 10 ) >= con1 ? con1 : me->query_skill("hamagong", 1) / 10 );
                target->apply_condition("snake_poison", con1 - con);
                message_vision(  HIW "$N盤膝坐下將手掌貼在$n背心，運功將$n體內的蛇毒吸出...\n片刻功夫，$N的掌心已全呈黑色。\n" NOR , me, target );
//                if ( !con1 )
    if ( (con1 - con)<=0 )
                        {
                                tell_object( target, HIC "你活動了一下筋骨，發覺全身的麻木感已完全消失了。\n\n" NOR );
                    target->clear_condition("snake_poison");
                  }
                else        
                        tell_object( target, HIC "你活動了一下筋骨，發覺全身的麻木感減輕了不少。\n\n" NOR );                        
                addn("neili", -100, me);
                me->apply_condition("snake_poison", me->query_condition("snake_poison") + con);
        }                         
        else if ( con3 > 0 ) {
                if ( (int)me->query_skill("hamagong", 1) < 70 )
                        return notify_fail("你的蛤蟆功修為不夠。\n");
                if( query("neili", me)<150 )
                        return notify_fail("你的真氣不夠。\n");
                con = ( ( me->query_skill("hamagong", 1) / 50 ) >= con3 ? con3 : me->query_skill("hamagong", 1) / 50 );
                target->apply_condition("xx_poison", con3 - con);
                message_vision(  HIW "$N盤膝坐下將手掌貼在$n背心，運功將$n體內的星宿掌毒吸出...\n"
                         "片刻功夫，$N的掌心已全呈紫黑色。\n" NOR , me, target );
//                if ( !con3 )
    if ( (con3 - con)<=0 )
                        {
                                tell_object( target, HIY "你只覺得一股暖流從丹田升起，全身熱乎乎的，星宿掌毒似乎已全除盡了。\n\n" NOR );
                    target->clear_condition("xx_poison");
      }
                else        
                        tell_object( target, HIY "你只覺得一股暖流從丹田升起，不似先前那般寒冷了。\n\n" NOR );                        
                addn("neili", -150, me);
                me->apply_condition("xx_poison", me->query_condition("xx_poison") + con);
        }
        set("jiali", 0, me);
        me->start_busy(4);
        return 1;
}
int help(object me)
{
        write(WHT"\n蛤蟆功之吸毒："NOR"\n");
        write(@HELP

        使用功效：
                為中毒的他人吸出毒素，對下列毒有效：
                蛇毒、星宿毒

        出手要求：
                蛤蟆功50級
                西毒毒技50級
                內力100
HELP
        );
        return 1;
}