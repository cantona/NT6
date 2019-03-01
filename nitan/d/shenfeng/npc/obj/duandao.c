#include <weapon.h>
inherit BLADE;

void create()
{
        set_name("哈薩克彎刀", ({ "hasake wandao", "hasake", "wandao", "dao", "blade" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄亮晃晃的哈薩克短刀, 是哈薩克人的防身武器。\n");
                set("value", 500);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲從腰間拔出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
        }
        init_blade(15);
        setup();
}