//bao3.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("素菜包子", ({"sucai baozi", "baozi"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("long", "一個香噴噴、熱騰騰的素菜灌湯包。\n");
                set("unit", "個");
                set("value", 25);
                set("food_remaining", 2);
                        set("food_supply", 40);
        }
}