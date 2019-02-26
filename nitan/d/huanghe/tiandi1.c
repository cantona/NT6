// Room: /huanghe/tiandi1.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "田地");
        set("long", @LONG
這裏林木漸漸稀疏，不遠處有一些村莊，炊煙裊裊升起。村莊周圍
是一塊塊的田地，田裏有一些正在耕作的農人。
LONG );
        set("exits", ([
                "south" : __DIR__"shulin3",
                "west"  : __DIR__"tiandi2",
                "east"  : __DIR__"tiandi3",
        ]));
        set("objects", ([
                "/d/village/npc/poorman" : 1,
        ]));
        set("outdoors", "huanghe");
        set("coor/x", -210);
        set("coor/y", 500);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}