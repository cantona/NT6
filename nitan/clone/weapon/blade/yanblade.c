// yanblade.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit BLADE;

void create()
{
        set_name("雁雲刀", ({"yanyun blade", "blade"}));
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "一把白燦燦的挽手胡刀，發着陰滲滲的殺氣．\n");
                set("value", 1500);
                set("material", "crimsonsteel");
                set("wield_msg", "$N「唰」地一聲抽出一把$n握在手中，臉色更加陰沉了！\n");
                set("unwield_msg","$N將手中的$n插入腰間，嘴角露出一絲笑意。\n");
                set("weapon_prop/courage", 10);
        }
        init_blade(40);
        setup();
}
