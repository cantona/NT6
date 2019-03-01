// yudi.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("碧玉笛", ({ "biyu di","yudi","biyudi", "di" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("value", 20000);
                set("material", "wood");
                set("long", "一根碧玉制就的笛子，綠瑩瑩地甚是精致。\n");
                set("wield_msg", "$N拿起一根$n放在唇邊輕輕一吹。\n");
                set("unwield_msg", "$N笑了一笑，將$n插回腰間。\n");
        }
        init_sword(15);
        setup();
}