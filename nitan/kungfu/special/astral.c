// This program is a part of NITAN MudLIB
// astral.c 破妄神瞳
// Created by Lonely@NITAN (04/05/2009)

#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_SSERVER;

string name() { return HIW "破妄神瞳" NOR; }

int perform(object me, string skill)
{
        string msg;
        int ap, dp;
        object target;

        if( !query("reborn/times", me) )
                return notify_fail("你尚未轉世重生，無法使用此技能！\n");

        if( !target ) { 
                me->clean_up_enemy(); 
                target = me->select_opponent(); 
        } 

        if( !target || !target->is_character() 
         || query("not_living", target) )
                return notify_fail("你打算對誰施展" + name() + "？\n");
                
        if( !me->is_fighting(target) ) 
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");      

        if( !query_temp("apply/shade_vision", target) )
                return notify_fail("對方並沒有運起隱身呀 ？\n");
       
        message_vision( HIR "$N" HIR "施展出破妄神瞳之術，無數星芒射向$n" 
                        HIR "。。。\n\n" NOR, me, target);

        ap = me->query_int(); 
        dp = target->query_dex();
        if( ap / 2 + random(ap) > dp ) {
                delete_temp("apply/shade_vision", target);
                message_vision( CYN "只聽$n" CYN "悶哼一聲，被星芒擊中，頓時無法隱身！\n\n" NOR, 
                                me, target );

                tell_object( target, HIW "你的隱身被" NOR + me->name() + HIW "破除了！\n\n" NOR );           
        } else 
                message_vision( HIY "只見$n" HIY "巧妙躲閃開$N" HIY "的星芒，"
                                HIY "隱身狀態絲毫沒有受到影響！\n\n" NOR, me, target );

        me->start_busy( 1 + random(2) );
        return 1;
}

