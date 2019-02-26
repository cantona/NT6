// pink_cloth.c

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(YEL"黃衫"NOR, ({ "yellow cloth", "cloth" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這件黃色的綢衫上面繡着幾隻紅花，聞起來還有一股淡香。\n");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("armor_prop/per", 3);
                set("female_only", 1);
        }
        setup();
}
