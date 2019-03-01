// faxisi.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "法喜寺");
        set("long", @LONG
法喜寺是天竺三寺中最敞朗深幽的一座。進香的遊客不時的進進
出出。往東可達龍井，朝北是下山的路。
LONG);
        set("exits", ([
                "eastdown"  : __DIR__"shanlu4",
                "northdown" : __DIR__"shanlu3",
        ]));
        set("objects", ([
            __DIR__"npc/guest" : 2,
            __DIR__"npc/seng" : 1,
        ]));
        set("outdoors", "hangzhou");
	set("coor/x", 750);
	set("coor/y", -2110);
	set("coor/z", 60);
	setup();
        replace_program(ROOM);
}