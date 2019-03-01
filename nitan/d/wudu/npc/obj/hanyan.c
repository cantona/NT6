#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("旱煙袋", ({ "han yan", "yan" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", "這是一只用了好多年的銅煙袋。\n");
                set("value", 100);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一只$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰帶中。\n");
        }
        init_sword(5);
        setup();
}