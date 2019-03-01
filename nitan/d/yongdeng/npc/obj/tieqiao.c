// tieqiao.c

#include <weapon.h>
inherit CLUB;

void create()
{
        set_name("鐵鍬", ({ "tie qiao", "qiao" }));
        set_weight(7000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一把挖礦的鐵鍬。\n");
                set("value", 1000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回後腰。\n");
        }
        init_club(2);
        setup();
}
