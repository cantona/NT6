#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("水蜜桃", ({"shuimi tao", "shuimi", "tao"}));
        set_weight(40);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "一碟水靈新鮮的水蜜桃，跟臉蛋兒一樣紅艷可人。\n" NOR);
                set("unit", "碟");
                set("value", 80);
                set("food_remaining", 4);
                set("food_supply", 30);
        }
}