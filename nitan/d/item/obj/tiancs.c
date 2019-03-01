// tiancs.c 冰蠶絲

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "冰蠶絲" NOR, ({ "white silk", "bingcan si", "si"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一束晶瑩剔透的細絲，隱然泛出白光。\n");
                set("unit", "束");
                set("value", 100000);
                set("item_origin", 1);
                set("material_attrib", "silk");
                set("material_name", HIW "冰蠶絲" NOR);
                set("can_make", ({ "鞭", "護甲", "戰衣", "靴子", "腰帶" }));
                set("power_point", 100);
        }
}
