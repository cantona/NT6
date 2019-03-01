// baipao.c 
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("白羅袍", ({"bailuo pao", "cloth"}));
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",
"一件白色的粗布袍，雖然質的並不好，但裁剪精細，看起來別有風姿。\n");
                set("material", "cloth");
                set("unit", "件");
                set("value", 400);
                set("armor_prop/armor", 15);

        }
        setup();
}
