// skirt.c
//
// This is the basic equip for players just login.

#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
        set_name(HIR"天蠶絲裙"NOR, ({ "skirt" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一件用天蠶絲織成的裙子，摸上去柔軟光滑。\n");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 150);
       }
        setup();
}
