// water_bottle.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("水壺", ({"water bottle", "bottle"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個不知道用什麼動物的皮製成的水壺。\n");
                set("unit", "個");
                set("value", 100);
                set("max_liquid", 10);
        }

        // because a container can contain different liquid
        // we set it to contain wine at the beginning
        set("liquid", ([
                "type": "water",
                "name": "清水",
                "remaining": 10,
                "drunk_supply": 5,
        ]));
}
