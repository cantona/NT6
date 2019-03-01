// baozi.c 包子

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("肉包子", ({"baozi", "bao"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個香噴噴的肉包子,不知道是用什麼肉做的。\n");
                set("unit", "個");
                set("value", 20);
                set("food_remaining", 3);
                set("food_supply", 20);
        }
}