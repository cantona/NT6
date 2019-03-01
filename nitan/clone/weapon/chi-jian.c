#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIR "熾劍" NOR, ({ "chi jian" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", NOR + HIR "這是一把渾身火紅的劍，提在手中感覺熾熱無比。\n" NOR);
                set("material", "tian jing");
                set("wield_msg", "$N「唰」的一聲抽出一把$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
                set("value", 100000);
        }
        init_sword(800);
        setup();
}
