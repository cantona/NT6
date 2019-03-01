// By rcwiz

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
    set_name(HIR "紅色長袍" NOR, ({"pao", "cloth", "chang pao"}) );
    set_weight(1500);
    if( clonep() )
            set_default_object(__FILE__);
    else {
        set("female_only", 1);
        set("unit", "件");
                set("long", "這是件質地輕軟的紅色長袍，邊上還鏤著花呢。\n");
        set("material", "cloth");
        set("armor_prop/armor", 1);
    }
    setup();
}