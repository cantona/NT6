// road12.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
沿湖大道旁店鋪林立，長街故樸，屋舍鱗次櫛比，道上人來車往，
一片太平熱鬧景象。街東邊是一古樸書院，書院裏不時傳來朗朗的笑聲。
LONG);
        set("exits", ([
                "north"     : __DIR__"road11",
                "south"     : __DIR__"road13",
                "east"      : __DIR__"shuyuan",
                "west"      : __DIR__"wjb_hzfb",
        ]));
        set("objects", ([
                __DIR__"npc/likexiu" : 1,
                __DIR__"npc/qingbing" : 4,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 830);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}