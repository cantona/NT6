// guishejiu.c 龜蛇酒壺

#include <ansi.h>;
inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("龜蛇酒壺", ({"guishe jiuhu", "jiu", "jiuhu"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個用來裝龜蛇酒的酒壺，裏面可裝一斤的酒。\n");
                set("unit", "個");
                set("value", 300);
                set("max_liquid", 15);
        }

        // because a container can contain different liquid
        // we set it to contain wine at the beginning
        set("liquid", ([
                "type": "alcohol",
                "name": "龜蛇酒",
                "remaining": 5,
                "drunk_apply": 3,
        ]));
}