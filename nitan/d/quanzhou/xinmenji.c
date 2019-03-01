// Room: /d/quanzhou/xinmenji.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "新門集");
        set("long", @LONG
這是泉州南面東西向的一條幹道，規模不大。南邊有家茶居，西邊
是新門吊橋，東邊則是市集。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"taoranju",
                "south" : __DIR__"taocipu",
                "east"  : __DIR__"jishi",
                "west"  : __DIR__"diaoqiao",
        ]));
	set("coor/x", -910);
	set("coor/y", -7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}