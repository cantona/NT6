// self.c 小周天運轉
// Created by Doing Lu 10/7/2K

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "小周天運轉" NOR; }

int perform(object me, string skill)
{
        int heal;

        if( query("jing", me)<80 )
                return notify_fail("你的精氣不夠，現在還不能施展小周天運轉。\n");

        if (me->is_fighting())
                return notify_fail("你正在打架，無法使用小周天運轉。\n");

        if( query("qi", me) >= query("eff_qi", me) )
                return notify_fail("你的體力很好，沒有必要使用小周天運轉。\n");

        message_vision(HIC "$N" HIC "雙手平舉，深深吐出了一"
                       "口氣，臉色變得圓潤多了。\n" NOR, me);
        tell_object(me, HIG "你感覺到你的氣力恢復了。\n" NOR);

        me->receive_damage("jing", 60 + random(20));
        heal = me->query_con() * 10;
        me->receive_heal("qi", heal);
        me->start_busy(1 + random(5));
        return 1;
}