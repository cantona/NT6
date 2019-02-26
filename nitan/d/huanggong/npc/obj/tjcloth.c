// tjcloth.c

#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("太監服飾", ({ "taijian cloth", "cloth" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","這是一件太監服飾，聞起來有一股説不出的惡臭。\n");
                set("unit", "件");
                set("value", 60);
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("armor_prop/per", 3);
        }
        setup();
}