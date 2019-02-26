// wine.c
#include <ansi.h>
inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name(MAG"月老仙水"NOR, ({"yuelao xianshui","xianshui"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "據説這是月老釀製的瓊漿，喝下去可以保佑姻緣，真是懸乎！\n");
                set("unit", "瓶");
                set("value", 10000);
                set("no_get", "1");
                set("max_liquid", 5);
        }

        set("liquid", ([
                "type": "alcohol",
                "name": HIW"仙水"NOR,
                "remaining": 5,
                "supply": 15,
                "drunk_apply": 3,
        ]));
}