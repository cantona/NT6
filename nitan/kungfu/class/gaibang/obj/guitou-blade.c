// guitou-blade.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit BLADE;

void create()
{
         set_name("鬼頭刀", ({"guitou dao", "dao", "blade" }) );
         set_weight(4000);
         if( clonep() )
                 set_default_object(__FILE__);
         else {
                 set("unit", "柄");
                 set("value", 2500);
                 set("material", "iron");
                 set("long", "這是一一把鬼頭刀，背厚刃薄，刀身甚長。\n");
                 set("wield_msg", "$N抽出一把明晃晃的$n握在手中。\n");
                 set("unequip_msg", "$N將手中的$n插入腰間的刀鞘。\n");
         }
         init_blade(45);
         setup();
}