// shanlu1.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit BUILD_ROOM;
void create()
{
        set("short", "山路");
        set("long", @LONG
一條被人走出來的山路，彎彎曲曲地向上延伸。走在山路上，只
見兩旁峰巒秀麗，景色怡人。不時有進香客擦肩而過。南上便到了下
天竺。北下就是大道。
LONG);
        set("exits", ([
                "southup"   : __DIR__"fajingsi",
                "northdown" : __DIR__"road2",
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
	set("coor/x", 750);
	set("coor/y", -2060);
	set("coor/z", 10);
	setup();
}
