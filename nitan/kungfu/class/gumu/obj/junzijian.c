// junzijian.c

#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIC "君子劍" NOR, ({ "junzi jian", "jian", "sword" }));
        set_weight(7000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一口遍體通黑的劍，劍身上用金絲錈着幾個字：\n"
                            "謙謙君子，温潤如玉\n");
                set("value", 12000);
                set("material", "steel");
                set("weapon_prop/per", 24);
                set("wield_msg", "$N低歎一聲，將$n緩緩抽出劍鞘。\n");
                set("unwield_msg", "$N手一晃，$n已然回鞘。\n");
        }
        init_sword(35);
        setup();
}