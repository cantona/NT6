// butian.c 補天石

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "補天石" NOR, ({"magic stone", "butian shi", "shi"}));
        set_weight(6000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "傳說這是女媧補天剩下的五彩石，不知是真是假。\n");
                set("unit", "塊");
                set("value", 10000);
                set("item_origin", 1);
                set("material_attrib", "magic stone");
                set("material_name", HIM "神鐵" NOR);
                set("can_make", "all");
                set("not_make", ({ "戰衣", "腰帶" }));
                set("power_point", 100);
        }
}
