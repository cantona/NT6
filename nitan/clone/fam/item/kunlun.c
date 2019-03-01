#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + CYN "昆侖石" NOR, ({"kunlun shi", "kunlun", "shi"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", CYN "這是一塊通體烏黑的石頭，石面沁出著絲絲寒意。\n" NOR);
                set("unit", "塊");
                set("value", 10000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + CYN "昆侖石" NOR);
                set("can_make", ({ "鐵掌" }));
                set("power_point", 70);
        }
}

int query_autoload()
{
        return 1;
}
