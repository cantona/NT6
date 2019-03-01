// pickaxe.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit AXE;

void create()
{
         set_name("鋤頭", ({ "pickaxe", "axe", "chutou", "chu" }) );
         set_weight(20000);
         if( clonep() )
                 set_default_object(__FILE__);
         else {
                 set("unit", "把");
                 set("long", "一把沉重的鋤頭，看上去很結實。\n");
                 set("value", 2000);
                 set("wield_msg", "$N拿出一把$n，一個沒拿穩，差點砸在自己腳上。\n");
                 set("unwield_msg", "$N放下手中的$n，氣喘吁吁地擦了擦汗。\n");
         }
         init_axe(20, TWO_HANDED);
         setup();
}