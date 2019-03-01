// ghost_sword.c
// Modified by haiyan

#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name(HIM"桃木劍"NOR, ({ "taomu jian", "jian" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 200);
                set("no_sell", 1);
                set("material", "bamboo");
        set("long", "這是一把道士們用來降妖除魔的桃木劍，上面刻著一些符號。\n");
                set("wield_msg", HIY"$N抽出一把金光閃閃的$n"HIY"握在手中。\n"); 
                set("unequip_msg", "$N放下手中的$n。\n");
        }
        init_sword(10);
        setup();
}
