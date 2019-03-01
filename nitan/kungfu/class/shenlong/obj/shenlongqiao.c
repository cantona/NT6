// tieqiao.c

#include <weapon.h>
inherit CLUB;

void create()
{
        set_name("鐵鍬", ({ "shenlong qiao", "tie qiao", "qiao" }));
        set_weight(17000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long","這是一把挖地的鐵鍬，用精鋼打制，木柄上雕著一條仰頭吐信的怪蛇。\n");
                set("value", 5000);
                set("material", "steel");
                set("no_put",1);
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回後腰。\n");
                set("dig_times", 5);
        }
        init_club(15);
        setup();
}
