#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(NOR + CYN "青罡劍" NOR, ({ "qinggang jian", "qinggang", "jian" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", NOR + CYN "這是一柄生鐵和青銅鑄造成的寶劍，頗為鋒利。\n" NOR);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
                set("value", 100000);
        }
        init_sword(300);
        setup();
}

int query_autoload()
{
        return 1;
}