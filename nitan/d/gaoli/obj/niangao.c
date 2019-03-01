// 粘糕。高麗特產。:-)

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("粘糕", ({"nian gao", "gao"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是高麗的特產粘糕。\n");
                set("unit", "個");
                set("value", 50);
                set("food_remaining", 3);
                set("food_supply", 20);
        }
}
