// xueshan-pao.c 
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("雪山白袍", ({"xueshan baipao", "baipao", "pao", "cloth"}));
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","一件絲制白袍，當胸繡著一只飛揚欲脫的大鵬鳥。\n");
                set("material", "cloth");
                set("unit", "件");
                set("value", 600);
                set("armor_prop/armor", 4);
                set("armor_prop/per", 1);
        }
        setup();
}

