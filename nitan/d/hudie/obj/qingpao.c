//qingpao.c 青袍

#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
        set_name(HIC"青衣長袍"NOR, ({"chang pao", "cloth", "pao"}) );
        set_weight(2000);
        if( clonep() )
            set_default_object(__FILE__);
        else {
        set("unit", "件");
        set("long", "這是一件質佳的青色長袍。\n");
        set("material", "cloth");
        set("armor_prop/armor", 20);
        set("value",2000);
    }
    setup();
}