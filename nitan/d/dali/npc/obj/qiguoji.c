// qiguoji.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("汽鍋雞", ({"qiguo ji", "chicken", "ji"}));
        set_weight(280);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一鍋熱氣騰騰的汽鍋雞。\n");
                set("unit", "鍋");
                set("value", 200);
                set("food_remaining", 10);
                set("food_supply", 40);
        }
}