#include <ansi.h>
#include <weapon.h>

inherit HAMMER;

void create()
{
        set_name("鋼杵", ({ "gang chu", "gang", "chu" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一柄全鋼鑄造的鋼杵。\n");
                set("value", 3000);
                set("material", "steel");
                set("wield_msg", "$N「呼」的一聲抽出一柄$n高舉在手中。\n");
                set("unwield_msg","$N將手中的$n揹回背上。\n");
                set("stable", 40);
        }
        init_hammer(50);
        setup();
}