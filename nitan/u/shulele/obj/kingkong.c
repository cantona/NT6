// This program is a part of NITAN MudLIB
// kingkong.c 大力金剛
// Created by Lonely@NITAN (04/05/2009)

#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_SSERVER;

string name() { return HIR "大力金剛" NOR; }

int perform(object me, string skill)
{
        object target;
        string msg;
        int ap, dp;

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

        if( !query_temp("special_skill/immortal", target) )
                return notify_fail("對方並沒有運起不死金身呀 ？\n");
       
        message_vision( HIR "$N" HIR "面色突然變得赤紅，雙手灌入巨大真力，"
                        HIR "重重一招襲向$n。\n\n" NOR, me, target);

        ap = me->query_str(); 
        dp = target->query_con();
        if( ap / 2 + random(ap) > dp ) {
                delete_temp("special_skill/immortal", target);
                message_vision( CYN "只聽$n" CYN "悶哼一聲，"
                                CYN "不死金身竟被$N" CYN "擊潰！\n\n" NOR, me, target );

                tell_object( target, HIW "你的不死金身被" NOR + me->name() +
                                    HIW "破除了！\n\n" NOR );           
        } else 
                message_vision( HIY "只見$n" HIY "硬生生接下$N" HIY "這一招，"
                                HIY "不死金身絲毫不為所動！\n\n" NOR, me, target );

        me->start_busy( 1 + random(2) );
        return 1;
}

