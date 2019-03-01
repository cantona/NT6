// mixian.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("過橋米線", ({"guoqiao mixian", "mixian"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一碗熱氣騰騰的油浸的米粉，正是大理名菜過橋米線。\n");
                set("unit", "碗");
                set("value", 80);
                set("food_remaining", 10);
                set("food_supply", 20);
        }
}