// jingtie.c 百鍊精鐵

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(WHT "百鍊精鐵" NOR, ({"iron", "tie"}));
        set_weight(4500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一塊黑黝黝的經過精心冶煉的精鐵。\n");
                set("unit", "塊");
                set("value", 5000);
                set("item_origin", 1);
                set("material_attrib", "iron");
                set("material_name", WHT "精鐵" NOR);
                set("can_make", "all");
                set("not_make", ({ "腰帶", "戰衣" }));
                set("power_point", 30);
        }
}