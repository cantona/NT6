// tofu.c 豆腐

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("翡翠豆腐", ({"doufu", "tofu"}));
        set_weight(40);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一塊水靈靈的大豆腐，嫩的令人不禁想到阿慶嫂的臉蛋兒。\n");
                set("unit", "塊");
                set("value", 40);
                set("food_remaining", 1);
                set("food_supply", 50);
        }
}