//Cracked by Kafei
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("蒸豆腐", ({"zheng doufu", "steamed tofu"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一碟蒸豆腐，有點象黃蓉燒過的「二十四橋明月夜」。\n");
                set("unit", "碟");
                set("value", 50);
                set("food_remaining", 1);
                set("food_supply", 15);
        }
}