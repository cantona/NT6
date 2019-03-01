// road11.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
沿湖大道旁店舖林立，長街故樸，屋舍鱗次櫛比，道上人來車往，
一片太平熱鬧景象。街東邊的一家店舖裡傳來叮叮當當的打鐵聲。
LONG);
        set("exits", ([
            "north"     : __DIR__"road10",
            "south"     : __DIR__"road12",
            "east"      : __DIR__"tiejiangpu",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 830);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}