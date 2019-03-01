// futou.c

#include <weapon.h>
inherit AXE;

void create()
{
        set_name("大斧頭", ({ "futou", "da futou" }));
        set_weight(7000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一把砍柴的大斧頭。\n");
                set("value", 1000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回後腰。\n");
        }
        init_axe(5);
        setup();
}
