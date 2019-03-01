// wujins.c 烏金絲

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(WHT "烏金絲" NOR, ({ "black silk", "wujin si", "si"}));
        set_weight(1800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一束黑白相間的細絲，是由烏金絲和蠶絲混合織就而成。\n");
                set("unit", "束");
                set("value", 20000);
                set("item_origin", 1);
                set("material_attrib", "silk");
                set("material_name", YEL "烏金絲" NOR);
                set("can_make", ({ "鞭", "護甲", "戰衣", "靴子", "腰帶" }));
                set("power_point", 70);
        }
}