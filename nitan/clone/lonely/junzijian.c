#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIW "君子劍" NOR, ({ "junzi jian", "jian", "junzi", "sword" }));
        set_weight(5000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIW "這是一口遍體通黑的劍，劍身上用金絲錈著幾個字：\n"
                            "謙謙君子，溫潤如玉。\n" NOR);
                set("unit", "柄");
                set("value", 60000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIW "$N" HIW "一聲清嘯，一柄無尖無鋒的寶劍已"
                                 "握在手中。\n" NOR);
                set("unwield_msg", HIW "$N" HIW "反轉劍身， 「唰」”的一聲，君"
                                   "子劍已然入鞘。\n" NOR);
                set("stable", 100);
        }
        init_sword(100);
        setup();
}