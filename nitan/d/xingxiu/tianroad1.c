// room: /d/xingxiu/tianroad1.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "天山山路");
        set("long", @LONG
這裏是天山東麓，山風從山上吹來，你冷得瑟瑟發抖。路邊是一片
草原。草原上一位牧羊人趕着一羣羊。這裏向東可以下山。北邊傳來陣
陣猛獸的嘯聲。
LONG );
        set("outdoors", "xiyu");
        set("exits", ([
                "eastdown" : __DIR__"shanjiao",
                "north"    : __DIR__"tianroad2",
        ]));
        set("objects", ([
                __DIR__"npc/herdsman" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -50000);
        set("coor/y", 10000);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}