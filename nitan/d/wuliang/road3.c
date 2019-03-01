// Room: /wuliang/road3.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "甬道");
        set("long", @LONG
這裡是劍湖宮內的甬道。東通正廳，西面是通往後山的小路。甬
道廊檐邊看下去，就是無量山景形勝了。
LONG );
        set("outdoors", "wuliang");
        set("exits", ([
                "west"  : __DIR__"road5",
                "east"  : __DIR__"zhengting",
        ]));
        set("objects", ([
                __DIR__"npc/yu" : 1,
        ]));
        set("coor/x", -71010);
        set("coor/y", -79890);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}