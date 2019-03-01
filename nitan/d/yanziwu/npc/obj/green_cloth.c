// green_cloth.c

#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("翠綠綢衫", ({ "green cloth", "cloth" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這件翠綠色的綢衫上面繡着幾隻黃鵲，聞起來還有一股淡香。\n");
                set("unit", "件");
                set("value", 600);
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("armor_prop/per", 3);
                set("female_only", 1);
        }
        setup();
}
