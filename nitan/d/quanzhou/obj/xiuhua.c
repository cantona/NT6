// weapon: xiuhua.c 繡花針
// Jay 4/7/96

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("繡花針", ({ "xiuhua zhen", "zhen", "needle" }));
        set_weight(5);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根精鋼細磨的繡花針，是繡花用的絕佳工具。\n");
                set("value", 100);
                set("material", "steel");
                set("wield_msg", "$N用拇指和食指從鬢間拈出一根$n。\n");
                set("unwield_msg", "$N將手中的$n插回鬢間。\n");
        }
        init_sword(10);
        setup();
}
