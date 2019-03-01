// junfu.c

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("黃衣軍服", ({ "junfu", "cloth" }));
        set("long", "這是一件有點舊的黃衣軍服。\n");
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("value", 200);
                set("armor_prop/armor", 5);
        }
        setup();
}