// madao.c

#include <weapon.h>
inherit BLADE;

void create()
{
        set_name("馬刀", ({ "ma dao", "blade", "dao" }));
        set_weight(7000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄磨得雪亮的馬刀，是哈薩克男子的標誌。\n");
                set("value", 1500);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回刀鞘。\n");
        }
        init_blade(25);
        setup();
}