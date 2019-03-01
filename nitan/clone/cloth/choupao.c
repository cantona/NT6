// choupao.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("綢袍", ({"chou pao", "pao", "cloth"}));
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","一件絲綢長袍，質的和裁剪都不錯．\n");
                set("material", "cloth");
                set("unit", "件");
                set("value", 600);
                set("armor_prop/armor", 4);
                set("armor_prop/per", 1);
        }
        setup();
}