//baijiu.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("粗劣酒瓶", ({"jiuping", "skin"}));
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "一個用來裝酒的酒瓶，能裝兩，三斤白酒。\n");
                set("unit", "個");
                set("value", 100);
                set("max_liquid", 15);
        }
        set("liquid", ([
                "type": "alcohol",
                "name": "劣質白酒",
                "remaining": 15,
                "drunk_supply": 15,
        ]));
}