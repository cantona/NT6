// wineskin.c  酒袋

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("牛皮酒袋", ({"jiudai", "wineskin", "skin"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個用來裝米酒的大酒袋，大概裝得八、九升的酒。\n");
                set("unit", "個");
                set("value", 20);
                set("max_liquid", 15);
        }

        // because a container can contain different liquid
        // we set it to contain wine at the beginning
        set("liquid", ([
                "type": "alcohol",
                "name": "米酒",
                "remaining": 15,
                "drunk_supply": 15,
        ]));
}
