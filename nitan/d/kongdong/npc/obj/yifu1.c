#include <armor.h>
inherit CLOTH;


void create()
{
        set_name("紫布長衫", ({ "cloth" }) );
        set("long","一件嶄新的衣服，看來費了許多手工。\n");
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("material", "cloth");
                set("value",400);
                set("armor_prop/armor", 1);
        }
        setup();
}
