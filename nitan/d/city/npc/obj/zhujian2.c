// zhujian2.c 竹劍
// 可以賣的竹劍，2兩銀子

#include <weapon.h>

inherit SWORD;

void create()
{
        set_name("竹劍", ({ "zhu jian", "jian", "sword"}) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 2000);
                set("material", "bamboo");
                set("long", 
"這是一把做工精致的竹劍，劍柄用細帆布包裹，劍身稍窄，劍尖處用布包了起來以免誤傷同伴。\n");
                set("wield_msg", "$N拿出一把練劍用的$n，握在手中。\n");
                set("unequip_msg", "$N放下手中的$n。\n");
        }
        init_sword(1);
        setup();
}
 