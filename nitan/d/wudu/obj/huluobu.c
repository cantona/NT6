// huluobu.c 胡籮卜
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("胡籮卜幹", ({"hu luobu", "luobu"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一塊晾幹了的胡籮卜幹，比較方便儲藏。\n");
                set("unit", "塊");
                set("value", 20);
                set("food_remaining", 3);
                set("food_supply", 20);
        }
}