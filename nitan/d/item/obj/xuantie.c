// xuantie.c 玄鐵石

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(CYN "玄鐵石" NOR, ({"xuan tie", "tie"}));
        set_weight(30000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一塊黑黝黝有些泛光石頭，掂在手中感到極為沉重，遠勝銅鐵。\n");
                set("unit", "塊");
                set("value", 30000);
                set("item_origin", 1);
                set("material_attrib", "steel");
                set("material_name", CYN "玄鐵" NOR);
                set("can_make", "all");
                set("not_make", ({ "鞭", "戰衣", "錘", "腰帶" }));
                set("power_point", 70);
        }
}