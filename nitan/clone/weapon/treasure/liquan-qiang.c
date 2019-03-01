// liquan-qiang.c 瀝泉槍
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>;
#include <weapon.h>;
inherit SPEAR;
inherit F_UNIQUE;

void create()
{
        set_name(HIW"瀝泉槍"NOR,({"liquan spear", "spear", "qiang"}));
        set_weight(100000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "桿");
                set("long","這是武穆遺物。當年岳武穆捻靈蛇而得神兵，百戰功成，多賴此槍。\n");
                set("material", "steel");
                set("no_drop", 1);
                set("value", 100);
                set("wield_msg", "$N「唰」的一聲提起一根$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n收回背後。\n");
        }
        init_spear(200);
        setup();
}