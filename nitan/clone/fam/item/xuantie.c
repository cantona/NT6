#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + CYN "天山玄鐵" NOR, ({ "tianshan xuantie", "tianshan", "xuantie" }));
        set_weight(20000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + CYN "世間極為罕見的玄鐵，採至天山，著手極為沉重。\n" NOR);
                set("unit", "塊");
                set("value", 30000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + CYN "天山玄鐵" NOR);
                set("can_make", ({ "劍", "刀" }));
                set("power_point", 100);
        }
}

int query_autoload()
{
        return 1;
}
