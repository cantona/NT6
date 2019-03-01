// Room: /huanghe/tiandi3.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "田地");
        set("long", @LONG
這裡是一大片農田。不遠處有一些村莊，炊煙裊裊升起。村莊周圍
是一塊塊的田地，田裡有一些正在耕作的農人。
LONG );
        set("exits", ([
                "west"      : __DIR__"tiandi1",
                "northeast" : __DIR__"tiandi4",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", -200);
        set("coor/y", 500);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}