// rice.c 大米飯

inherit ITEM;

void init();
inherit F_FOOD;

void create()
{
        set_name("米飯",({"rice", "mi fan", "fan" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一碗剛從鍋裡盛出來的大米飯，還冒著熱氣～～～\n");
                set("unit", "碗");
                set("value", 120);
                set("food_remaining", 5);
                set("food_supply", 40);
        }
}

