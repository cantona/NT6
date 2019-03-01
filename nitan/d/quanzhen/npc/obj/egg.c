// egg.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("五香茶葉蛋", ({"spicy egg", "egg"}));
        set_weight(60);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一顆用五種香料炮製出來的茶葉蛋。\n");
                set("unit", "顆");
                set("value", 50);
                set("food_remaining", 1);
                set("food_supply", 50);
        }
}