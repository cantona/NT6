// bayuban.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit HAMMER;

void create()
{
         set_name("白玉板", ({ "baiyu ban", "baiyuban", "yuban", "ban" }) );
         set_weight(1000);
         if( clonep() )
                 set_default_object(__FILE__);
         else {
                 set("unit", "塊");
                 set("value", 10000);
                 set("material", "wood");
                 set("long", "一塊白玉制就的板子，沉甸甸地甚是壓手。\n");
                 set("wield_msg", "$N拿起一塊$n拍了拍掌心。\n");
                 set("unwield_msg", "$N將$n插回腰間。\n");
         }
         init_hammer(15);
         setup();
}