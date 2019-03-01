// This program is a part of NITAN MudLIB
// recover.c 破元大法
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "破元大法" NOR; }

int perform(object me, string skill)
{
        mapping my;

        if( !query("reborn/times", me) )
                return notify_fail("你尚未轉世重生，無法使用此技能！\n");
            
        if( time()-query("special/recover", me)<1440 )
                return notify_fail("破元大法一天只能施展一次！\n");

        message_vision(HIC "$N" HIC "施展出破元大法，真氣突破奇經八脈，恢復所有狀態！\n" NOR, me);
       
        set("special/recover", time(), me);
        
        my = me->query_entire_dbase();
        my["jing"]   = my["eff_jing"]   = my["max_jing"];
        my["jingli"] = my["eff_jingli"] = my["max_jingli"];
        my["qi"]     = my["eff_qi"]     = my["max_qi"];
        my["neili"]  = my["max_neili"] * 2;
        my["food"]   = me->max_food_capacity();
        my["water"]  = me->max_water_capacity();

        me->clear_condition();

        return 1;
}

