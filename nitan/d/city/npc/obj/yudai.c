// yudai.c

#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name(CYN"玉帶"NOR, ({"yu dai", "dai" }));
        set_weight(500);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "白玉雕成的玉帶，觸手細膩清涼。\n");
                set("unit", "只");
                set("value", 120000);
                set("material", "gold");
                set("armor_prop/armor", 12);
        }
        setup();
}
