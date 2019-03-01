// gunny_shoes.c

#include <armor.h>

inherit BOOTS;

void create()
{
        set_name("麻鞋", ({ "gunny shoes", "shoes" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "雙");
                set("long", 
"這是一雙麻布鞋，不易大滑，供遊人登山使用。\n");
                set("value", 150);
                set("material", "cloth");
                set("armor_type", "boots");
                set("armor_prop/armor", 1);
        }

}