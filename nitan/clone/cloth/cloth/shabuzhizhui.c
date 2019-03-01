// shabu_zhizhui.c 紗布直綴

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("紗布直綴", ({"shabu zhizhui", "cloth"}));
        set_weight(1500);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一套黑紗布的對襟衣服，常見和尚行者穿著。\n");
                set("unit", "套");
                set("value", 300);
                set("material", "cloth");
                set("armor_prop/armor", 1);
        }
        setup();
}


