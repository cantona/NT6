//teapot.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("茶壺", ({ "tea pot", "pot" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("long", "一個茶館賣的茶壺，大概裝得幾升水。\n");
                set("unit", "個");
                set("value", 30);
                set("max_liquid", 10);
        }
        set("liquid", ([
                "name": "茶水",
                "remaining": 10,
        ]));
}