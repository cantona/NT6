// biyuqiang.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit SPEAR;

void create()
{
        set_name("碧玉雙槍", ({ "jade spear", "spear" }));
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "桿");
                set("long","一對玉制的青色短槍，象是有錢人家的擺設，卻又鋒利無比．\n");
                set("value", 9000);
                set("material", "blacksteel");
                set("wield_msg","$N雙手一分，從背後解下一對短槍握到手中．\n");
                set("unwield_msg", "$N將手中的$n系到背後．\n");
        }
        init_spear(20);
        setup();
}
