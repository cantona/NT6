// agile.c 如鬼似魅
// Created by Doing Lu 10/7/2K

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "如鬼似魅" NOR; }

int perform(object me, string skill)
{
        int count;

        if( query("qi", me)<80 )
                return notify_fail("你的體力不支，無法竭力提升自己的速度。\n");

        message_vision(HIC "$N" HIC "腳尖一點，踢起一些塵"
                       "土，整個人頓時如同紙鷂一般飄飄忽忽。\n" NOR, me);
        count = me->query_dex();

        if( query_temp("special_skill/agile", me) )
                return notify_fail("你已經竭力提升你自己的速度了。\n");

        me->receive_damage("qi", 40 + random(40));
        set_temp("special_skill/agile", 1, me);
        addn_temp("apply/dodge", count, me);
           me->start_call_out((: call_other, __FILE__, "remove_effect", me,
                              count :), 60 + random(30));

        return 1;
}

void remove_effect(object me, int count)
{
        delete_temp("special_skill/agile", me);
        addn_temp("apply/dodge", -count, me);
        tell_object(me, "你的如鬼似魅施展完畢，身形一頓，又慢了下來。\n");
}
