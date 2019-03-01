// kenao.c

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("窄裉襖", ({ "ken ao" }));
        set("long", "這是一件少數民族常用的窄裉襖。\n");
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("value", 400);
                set("armor_prop/armor", 5);
        }
        setup();
}