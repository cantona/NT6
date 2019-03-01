//Cloth :xiaogua.c

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("青紗小褂", ({ "xiao gua", "cloth"}) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一套青紗布的褂子，略小了點，好象是童裝。\n");
                set("value", 60);
                set("unit", "套");
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("kidonly", 1);
        }
        setup();
}