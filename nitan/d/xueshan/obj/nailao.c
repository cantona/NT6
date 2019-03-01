// nailao.c 奶酪

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("奶酪", ({ "nai lao", "nailao" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一塊乳黃色的奶酪。\n");
                set("unit", "塊");
                set("value", 150);
                set("food_remaining", 5);
                set("food_supply", 60);
        }
}
