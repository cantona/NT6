// road10.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
沿湖大道旁店鋪林立，長街故樸，屋舍鱗次櫛比，道上人來車往，
一片太平熱鬧景象。街的東邊是一座酒樓。
LONG);
        set("exits", ([
            "north"     : __DIR__"road9",
            "south"     : __DIR__"road11",
            "east"      : __DIR__"jiulou",
            "west"      : __DIR__"marryroom",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 830);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}