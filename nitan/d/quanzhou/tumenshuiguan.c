// Room: /d/quanzhou/tumenshuiguan.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "塗門水關");
        set("long", @LONG
這是去往港口的主要通道，橫跨小溪之上，巍然矗立，可謂巧手天
成，別具一格。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west" : __DIR__"tumenji",
                "east" : __DIR__"lingshan",
        ]));
	set("coor/x", -880);
	set("coor/y", -7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}