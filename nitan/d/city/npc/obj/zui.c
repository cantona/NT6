// zui.c  神仙醉
// created by cpu 2002
#include <ansi.h>
inherit ITEM;
void setup()
{}
void init()
{
        add_action("do_drink", "drink");
}
void create()
{
        set_name(HIG"神仙醉酒"NOR, ({"shenxian zui", "jiubei"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIB"一隻外型奇特的酒杯，裏面裝的似乎是一種烈性白酒。\n"NOR);
                set("unit", "杯");
                set("value", 5000);
                
        }

}

int do_drink(string arg)
{
            int drk;
            object me;
            me =  this_player();
        drk=(query("con", me)+query("max_neili", me)/50)*2;
            
if (!id(arg))
        return notify_fail("你要喝什麼？\n");
me->apply_condition("drunk",drk-1);
message_vision(HIG"$N喝下一杯神仙醉酒，看上去頓時有了幾分醉意！\n"NOR,me);
        destruct(this_object());
        return 1;
}
