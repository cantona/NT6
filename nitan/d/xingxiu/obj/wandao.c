// weapon: /z/xingxiu/npc/obj/wandao.c
// Jay 3/17/96

#include <weapon.h>
inherit BLADE;

void create()
{
        set_name("阿拉伯彎刀", ({ "wandao" }));
        set_weight(6000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄亮晃晃的阿拉伯彎刀，刀身呈新月狀，是中東"
"地區最常見的兵刃。\n");
                set("value", 1500);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回刀鞘。\n");
        }
        init_blade(20);
        setup();
}