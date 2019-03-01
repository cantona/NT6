 
inherit ITEM;
inherit F_FOOD;

void create()
{
   set_name("蛇膽", ({"she dan","dan"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一個蛇膽，可以食用，也可以用來煉藥。\n");
                set("unit", "個");
                set("value", 100);
                set("food_remaining", 20);
                set("food_supply", 50);
                                set("heal",([
                                        "heals":60,
                                        ]));
        }
}
