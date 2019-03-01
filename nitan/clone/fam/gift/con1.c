#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(NOR + WHT "壯骨粉" NOR, ({ "zhuanggu fen", "zhuanggu", "fen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", WHT "這是一包灰黑色的藥粉，據說吃了可以增強根骨。\n" NOR);
                set("base_unit", "包");
                set("base_value", 10000);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("gift_type", "con");
                set("gift_name", "先天根骨");
                set("gift_point", 40);
                set("gift_msg", HIM "突然你渾身骨骼響個不停，但隨即又平和了下來。\n" NOR);
        }
        setup();
}
