// caidao.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit BLADE;

void create()
{
         set_name("菜刀", ({ "cai dao", "dao", "knife" }) );
         set_weight(1000);
         if( clonep() )
                 set_default_object(__FILE__);
         else {
                 set("unit", "柄");
                 set("value", 100);
                 set("material", "iron");
                 set("long", "這是一尋常的菜刀，份量大約六、七斤重。\n");
                 set("wield_msg", "$N抽出一把血淋淋的$n握在手中。\n");
                 set("unequip_msg", "$N放下將手中的$n。\n");
         }
         init_blade(10);
         setup();
}