//hulu2.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("葫蘆", ({"bhulu", "hu"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個藍色的葫蘆。\n");
                set("unit", "個");
                set("value", 100);
                set("max_liquid", 3);
        }
        // because a container can contain different liquid
        // we set it to contain water at the beginning
        set("liquid", ([
                "type": "alcohol",
                "name": "藥酒",
                "remaining": 3,
                "drunk_supply": 10,
        ]));
}