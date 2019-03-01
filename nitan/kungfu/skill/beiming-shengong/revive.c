// This program is a part of NITAN MudLIB
// revive.c

// 虛竹見了她的傷勢，想起聰辯先生蘇星河曾教過他這門治傷之法，當即催駝近前，
// 左手中指連彈，已封閉了那女子斷臂處的穴道，血流立止。第六次彈指時，使的
// 是童姥所教的一招‘星丸跳擲’，一股的北冥真氣射入她的臂根‘中府穴’中。那女
// 子“啊”的一聲大叫，醒了轉來，

#include <ansi.h>

int exert(object me, object target)
{       
        if( !target )           
                return notify_fail("你自己是清醒的嗎？\n");     

        if( me->is_fighting() || target->is_fighting())         
                return notify_fail("戰鬥中無法運功！\n");       

        if(target == me)                
                return notify_fail("你不能對自己運功！\n");     

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不夠。\n");     

        if( query("neili", me)<350 )
                return notify_fail("你的真氣不夠。\n");        

        if( living(target) )            
                return notify_fail( target->name() +"已經是清醒的！\n");        

        message_vision(HIY "$N左手中指連彈，一招‘星丸跳擲’，一股真氣射入$n的臂根‘中府穴’中。\n\n" NOR,me, target );    

        target->revive(); 
        
        addn("neili", -250, me);
        set("jiali", 0, me);
        me->start_busy(2);                
        target->start_busy(2);  

        return 1;
}