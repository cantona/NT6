// Jay May 27, 96

#include <weapon.h>
inherit WHIP;

void create()
{
        set_name("拂塵", ({ "fuchen" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄拂塵，做工精細，是很陰毒的兵器。\n");
                set("value", 30);
                set("material", "leather");
                set("wield_msg", "$N「唰」的一聲從頸中抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n別回頸中。\n");
        }
        init_whip(20);
        setup();
}
