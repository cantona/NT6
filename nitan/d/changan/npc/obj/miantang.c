//miantang.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("麪湯", ({"mian tang", "miantang", "mian"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("long", "一碗熱氣騰騰的麪湯。\n");
                set("unit", "碗");
                set("value", 100);
                set("food_remaining", 5);
                set("food_supply", 10);
        }
}