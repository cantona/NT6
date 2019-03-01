#include <ansi.h>
#include <armor.h>

inherit NECK;

void create()
{
        set_name( BLU "人頭鏈" NOR, ({ "rentou lian", "lian" }) );
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "串");
                set("long", "這是一條用一個個骷髏串起來的人頭鏈。\n");
                set("value", 150);
                set("material", "neck");
                set("armor_prop/armor", 7);
        }
        setup();
}

