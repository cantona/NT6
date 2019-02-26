// jinpao.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("錦花袍", ({"jinhua pao","cloth","pao"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long",
"這是一件華貴無比的錦花袍，上面繡着各種花草，還有一股香氣．\n");
                set("value", 5000);
                set("material", "cloth");
                set("armor_type", "cloth");
                set("armor_prop/armor", 10);
                set("armor_prop/per", 3);
        }
        setup();
}
