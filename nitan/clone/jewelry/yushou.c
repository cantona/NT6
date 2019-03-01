// yushou.c

#include <ansi.h>
#include <armor.h>

inherit WRISTS;

void create()
{
        set_name(CYN"玉手鐲"NOR, ({"yu shouzhuo", "shuozhuo" }));
        set_weight(500);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "白玉雕成的手鐲，紋理清晰，圓滑光澤。\n");
                set("unit", "枚");
                set("value", 100000);
                set("material", "gold");
                set("armor_prop/armor", 10);
        }
        setup();
}

