// white-robe.c 白色道袍

#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("白色道袍", ({"pao", "cloth", "dao pao"}) );
        set_weight(4500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", "這是件素雅潔凈的白色道袍。\n");
                set("material", "cloth");
                set("armor_prop/armor", 3);
        }
        setup();
}