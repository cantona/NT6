// This program is a part of NITAN MudLIB
// immortal.c 不死金身
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return YEL "不死金身" NOR; }

int perform(object me, string skill)
{
        if( !query("reborn/times", me) )
                return notify_fail("你尚未轉世重生，無法使用此技能！\n");
            
        if( time()-query("special/immortal", me)<3600 )
                return notify_fail("你要過些時候才能再用此技能！\n");

        message_vision(YEL "$N" YEL "臉色一沉，全身散發出一陣金光，"
                       YEL "便如羅漢轉世一般。\n" NOR, me);

        set_temp("special_skill/immortal", 1, me);
        set("special/immortal", time(), me);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 30);
        return 1;
}

void remove_effect(object me)
{
        delete_temp("special_skill/immortal", me);
        tell_object(me, "你施展完不死金身，鬆了一口氣。\n");
}
