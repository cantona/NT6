// wdahui.c

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("烏夷大麾", ({ "da hui" }));
        set("long", "這是一件烏夷大麾。\n");
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("value", 200);
                set("armor_prop/armor", 3);
        }
        setup();
}