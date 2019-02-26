#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "無名之物加強型" NOR, ({"noname object", "noname", "object"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", sort_msg(HIM "非金非玉非石非木無名之物，看似平凡"
                                         "但又似不平凡，忽隱忽現，忽明忽暗。"
                                         "似乎包容着不為人知的力量，但卻感覺"
                                         "不到一點能量。\n" NOR));
                set("unit", "塊");
                set("value", 20000000);
                set("item_origin", 1);
                set("material_attrib", "noname object");
                set("material_name", HIM "無名之物" NOR);
                set("can_make", "all");
                set("power_point", 300);
                set("item/point", 2700);
        }
}