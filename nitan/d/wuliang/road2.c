// Room: /wuliang/road2.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "甬道");
        set("long", @LONG
這裏是劍湖宮內的甬道。西通正廳，東面是個很大的花園。甬道
廊檐邊看下去，就是無量山景形勝了。
LONG );
        set("outdoors", "wuliang");
        set("exits", ([
                "east"  : __DIR__"huayuan",
                "west"  : __DIR__"zhengting",
        ]));
        set("objects", ([
                __DIR__"npc/wu" : 1,
        ]));
        set("coor/x", -70990);
        set("coor/y", -79890);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}