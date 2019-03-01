// zongzi.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("粽子", ({"zongzi"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個香噴噴的肉粽子，包它的粽子葉泛出一股清香。\n");
                set("unit", "個");
                set("value", 100);
                set("food_remaining", 3);
                set("food_supply", 50);
        }
}
