// road13.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
沿湖大道旁店鋪林立，長街故樸，屋舍鱗次櫛比，道上人來車往，
一片太平熱鬧景象。街東邊有一家客店。
LONG);
        set("exits", ([
            "north"     : __DIR__"road12",
            "southwest" : __DIR__"road14",
            "east"      : __DIR__"kedian",
        ]));
        set("objects", ([
            __DIR__"npc/zhang": 1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 830);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}