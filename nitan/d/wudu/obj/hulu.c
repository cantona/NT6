// hulu.c 

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("葫蘆", ({"hulu", "hu"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個用葫蘆制成的水壺。\n");
                set("unit", "個");
                set("value", 100);
                set("max_liquid", 10);
        }
        set("liquid", ([
                "type": "water",
                "name": "清水",
                "remaining": 10,
                "drunk_supply": 10,
        ]));
}