// sickle.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit BLADE;

void create()
{
         set_name("鐮刀", ({ "sickle", "dao", "blade", "lian", "lian dao" }) );
         set_weight(1500);
         if( clonep() )
                 set_default_object(__FILE__);
         else {
                 set("unit", "柄");
                 set("value", 200);
                 set("material", "wood");
                 set("long", "這是一柄農村中常見的鐮刀。\n");
                 set("wield_msg", "$N抽出一把$n握在手中，刀刃上還帶着稻草。\n");
                 set("unequip_msg", "$N將手中的$n別回腰帶裏。\n");
         }
         init_blade(5);
         setup();
}