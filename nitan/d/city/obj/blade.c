// blade.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit BLADE;

void create()
{
         set_name("鋼刀", ({"gang dao", "gangdao", "dao", "blade" }) );
         set_weight(4000);
         if( clonep() )
                 set_default_object(__FILE__);
         else {
                 set("unit", "柄");
                 set("value", 500);
                 set("material", "iron");
                 set("long", "這是一尋常的單刀，份量大約六、七斤重。\n");
                 set("wield_msg", "$N抽出一把明晃晃的$n握在手中。\n");
                 set("unequip_msg", "$N將手中的$n插入腰間的刀鞘。\n");
         }
         init_blade(25);
         setup();
}