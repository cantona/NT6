// jinchuang-yao.c 金創藥

#include <ansi.h>

inherit ITEM;

void create()
{

        set_name("金創藥", ({"jin chuangyao", "yao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("long", "這是一包別具靈效的少林金創藥，專治內外傷等。\n");
                set("value", 2000);
                set("only_do_effect", 1);
        }

        set("shaolin",1);
        setup();
}

int do_effect(object me)
{
        if( query("eff_qi", me) == query("max_qi", me) )
                return notify_fail("你現在不需要用金創藥。\n");
        
        me->start_busy(1);
        me->receive_curing("qi", 50);
        message_vision(HIC "$N" HIC "吃下一包金創藥，只覺精神振"
                       "作，氣色看起來好多了。\n" NOR, me);

        destruct(this_object());
        return 1;
}
