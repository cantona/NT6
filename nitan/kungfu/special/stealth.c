// This program is a part of NITAN MudLIB
// stealth.c 仙隱迷蹤
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIK "仙隱迷蹤" NOR; }

int perform(object me, string skill)
{
        if( !query("reborn/times", me) )
                return notify_fail("你尚未轉世重生，無法使用此技能！\n");
            
        if( time()-query("special/stealth", me)<21600 )
                return notify_fail("你要過些時候才能再用此技能！\n");

        message_vision(HIK "$N" HIK "施展出仙隱迷蹤，身影越來越淡，漸漸隱身不見了。\n" NOR, me);

        set_temp("apply/shade_vision", 1, me);
        set("special/stealth", time(), me);
        if( me->is_fighting() && me->is_busy() ) {
                me->remove_all_killer(); 
                all_inventory(environment(me))->remove_killer(me); 
                me->stop_busy();
        }
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 30);
        return 1;
}

void remove_effect(object me)
{
        delete_temp("apply/shade_vision", me);
        tell_object(me, "你施展完仙隱迷蹤，鬆了一口氣。\n");
        message_vision(HIK "$N" HIK "的身形逐漸顯露出來，變的清晰可見。\n" NOR, me);
}
