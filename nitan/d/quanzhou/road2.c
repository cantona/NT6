// Room: /d/quanzhou/road2.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "街道");
        set("long", @LONG
這是泉州的一條幹道，兩邊種着鳳凰木，人馬川流不息。南去可達
海外交通使節府，東面是萬國煙雨樓。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "east"   : __DIR__"yanyu",
                "north"  : __DIR__"road1",
                "south"  : __DIR__"shibosi",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -890);
	set("coor/y", -7740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}