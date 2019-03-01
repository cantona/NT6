// jjunfu.c

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("錦衣軍服", ({ "junfu", "cloth" }));
        set("long", "這是一件顏色鮮亮的錦衣軍服。\n");
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("value", 1200);
                set("armor_prop/armor", 15);
        }
        setup();
}