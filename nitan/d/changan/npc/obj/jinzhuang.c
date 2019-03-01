//jinzhuang.c

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIB"藍色勁裝"NOR, ({ "jin zhuang" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else 
        {        
                set("unit", "件");
                set("long", "這是一套短打勁裝。\n");
                set("value", 1000);
                set("material", "cloth");
                set("armor_prop/armor", 2);
        }

        setup();
}