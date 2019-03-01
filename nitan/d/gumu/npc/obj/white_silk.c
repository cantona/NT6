// white_silk 白紗裙
// 01/08/03
// Code by April

#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
        set_name("白紗裙", ({ "white skirt","skirt" }) );
                //set_color("$HIW$");
        set_weight(800);
        
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                        set("long", "一件潔白的紗裙。\n");
            set("material", "cloth");
            set("value", 0);
            set("armor_prop/armor", 8);
            set("armor_prop/per", 5);
            set("female_only", 1);
        }

        setup();
}
