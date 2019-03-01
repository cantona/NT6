// Room: /d/quanzhou/road1.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "街道");
        set("long", @LONG
這是泉州南面東西向的一條幹道，規模不大。南去可達海外交通使
節府，東面是一所綢緞莊。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "east"   : __DIR__"chouduan",
                "south"  : __DIR__"road2",
                "north"  : __DIR__"tumenji",
        ]));
        set("objects", ([
                "/d/city/npc/liumangtou" : 1,
        ]));
	set("coor/x", -890);
	set("coor/y", -7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}