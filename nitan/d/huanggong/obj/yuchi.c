// yuchi.c 魚翅

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("魚翅", ({"yu chi", "yu"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "上等魚翅，味道鮮美。其實也就那麼回事。\n");
                set("unit", "碟");
                set("value", 100);
                set("food_remaining", 1);
                set("food_supply", 1);
        }
}
