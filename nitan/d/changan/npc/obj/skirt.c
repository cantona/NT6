//skirt.c

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name("輕紗長裙", ({ "skirt", "cloth" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("long", "一條朦朦朧朧的紗裙，聞起來還有一股淡香。\n");
                set("unit", "條");
                set("value", 0);
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("armor_prop/per", 3);
                set("female_only", 1);
        }

        setup();
}