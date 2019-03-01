// sengpao.c
// Last Modified by winder on May. 25 2001
 
#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("僧袍", ({ "seng pao", "pao", "cloth" }) );
        set("long", "這是一件尋常的僧袍，是和尚們的普通裝束。\n");     
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 5);
                set("armor_prop/spells", 5);
        }
        setup();
}
