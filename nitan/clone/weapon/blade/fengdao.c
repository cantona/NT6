// fengdao.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit BLADE;

void create()
{
         set_name("鳳月刀", ({"fengyue dao", "dao", "blade"}) );
         set_weight(6000);
         if( clonep() )
                 set_default_object(__FILE__);
         else {
                 set("unit", "柄");
                 set("value", 500);
                 set("material", "iron");
                 set("long", "這是一柄漂亮的雙鳳戲月刀。\n");
                 set("wield_msg", "$N抽出一柄$n，唰地握在手中。\n");
                 set("unequip_msg", "$N將手中的$n插入腰間的刀鞘。\n");
         }
         init_blade(55);
         setup();
}