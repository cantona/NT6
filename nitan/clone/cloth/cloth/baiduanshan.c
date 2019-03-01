// baiduanshan.c  白緞衫

#include <armor.h>
inherit CLOTH;
void create()
{
        set_name("白緞衫", ({"baiduan shan", "cloth"}));
        set_weight(1000);
        if ( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("long", "一套白色的綢衫，柔軟飄逸。\n");
                set("unit", "套");
                set("value", 800);
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("armor_prop/per", 2);
        }
        setup();
}