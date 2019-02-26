// Room: /d/yanziwu/bridge.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "碧玉小橋");
        set("long", @LONG
碧玉小橋橫跨在清溪之上。橋下溪水清如翡翠，温如潤玉。漢白玉
小橋上爬滿青藤，滿目生綠，十分可人。
LONG );
        set("outdoors", "mantuo");
        set("exits", ([
                "west"  : __DIR__"path2",
                "east"  : __DIR__"path3",
        ]));
        set("objects", ([
                __DIR__"npc/xiaolan" : 1,
        ]));
        set("coor/x", 1220);
        set("coor/y", -1290);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}