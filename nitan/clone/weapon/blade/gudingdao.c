// gudingdao.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit BLADE;

void create()
{
         set_name("古錠刀", ({"guding dao", "dao", "blade", }) );
         set_weight(10000);
         if( clonep() )
                 set_default_object(__FILE__);
         else {
                 set("unit", "柄");
                 set("value", 0);
                 set("no_sell", 1);
                 set("no_give", 1);
                 set("no_drop", 1);
                 set("no_put", 1);
                 set("material", "steel");
                 set("long", "一把鏽跡斑駁的長刀，份量相當的沉重。\n");
                 set("wield_msg", "$N抹了抹$n上的灰塵，握在手裏。\n");
                 set("unequip_msg", "$N將$n綁到身後。\n");
         }
         init_blade(60);
         setup();
}