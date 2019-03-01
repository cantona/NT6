// xiaoao.c

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("圓領小襖", ({ "xiao ao", "cloth" }));
        set("long", "這是一件台夷族的圓領小襖。\n");
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("value", 300);
                set("armor_prop/armor", 1);
        }
        setup();
}