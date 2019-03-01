// water.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("杯盞", ({"water"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "還沒定義，等下層調用。\n");
                set("unit", "杯");
                set("value", 100);
                set("no_get", "1");
                set("max_liquid", 5);
        }

        set("liquid", ([
                "type": "water",
                "name": "清水",
                "remaining": 5,
                "supply": 10,
                "drunk_apply": 3,
        ]));
}