// shanlu4.c
#include <room.h>
inherit BUILD_ROOM;
void create()
{
        set("short", "山路");
        set("long", @LONG
走在這彎彎的小路上，看着沿途山峯雲影，松竹青葱，巖石斑駁。
不禁感到胸懷舒暢。西上便到了上天竺。東下就到了龍井。
LONG);
        set("exits", ([
            "westup"   : __DIR__"faxisi",
            "eastdown" : __DIR__"shanlu5",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "hangzhou");
	set("coor/x", 760);
	set("coor/y", -2110);
	set("coor/z", 50);
	setup();
}
