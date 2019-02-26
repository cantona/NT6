// Room: /city/duchang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "賭場");
        set("long", @LONG
這裏有四條走廊通向不同的房間。四周是拱豬小屋。
LONG );
	set("exits", ([
		"east"  : __DIR__ "eproom",
		"west"  : __DIR__ "wproom",
		"south" : __DIR__ "sproom",
		"north" : __DIR__ "nproom",
		"down"  : "/d/city/duchang",
	]));
	set("coor/x", -10);
	set("coor/y", -10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}