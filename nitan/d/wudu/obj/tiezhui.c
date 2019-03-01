// tiechui.c 大鐵錘

#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name("大鐵錘", ({ "tiechui", "chui","hammer" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄沉重的大鐵錘，後面帶著長長的鐵鏈。\n");
                set("value", 300);
                set("material", "steel");
                set("wield_msg", "$N「嘩啷」的一聲,取出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n掛回腰間。\n");
        }
        init_hammer(30);
        setup();
}