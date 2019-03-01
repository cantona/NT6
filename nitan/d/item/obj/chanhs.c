// chanhs.c 纏魂絲

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(WHT "纏魂絲" NOR, ({"silk", "chan hunsi", "si"}));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一束晶瑩透明的細絲，是用蛛絲和蠶絲混合織就而成的。\n");
                set("unit", "束");
                set("value", 10000);
                set("item_origin", 1);
                set("material_attrib", "silk");
                set("material_name", WHT "纏魂絲" NOR);
                set("can_make", ({ "鞭", "護甲", "戰衣", "靴子", "腰帶" }));
                set("power_point", 35);
        }
}