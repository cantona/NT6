// mandao.c

#include <weapon.h>
inherit BLADE;

void create()
{
        set_name("蠻刀", ({ "man dao", "dao", "blade" }));
        set_weight(7000);
        set("taskobj", 1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄亮晃晃的蠻刀，是雲貴少數民族首領的常備武器。\n");
                set("value", 0);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回刀鞘。\n");
        }
        setup();
}