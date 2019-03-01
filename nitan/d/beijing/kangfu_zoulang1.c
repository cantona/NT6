#include <room.h>
inherit ROOM;

void create()
{
        set("short", "康府走廊");
        set("long", @LONG
這是一條木制的走廊，地面很是光滑，被打整得一塵不染。幾個
康府的下人在此走動。南邊是康府的大院，北邊則是康府的大廳了。
LONG );
       set("exits", ([
                "north" : "/d/beijing/kangfu_dating",
                "south" : "/d/beijing/kangfu_dayuan",
        ]));
        set("objects", ([
                "/d/beijing/npc/jiading_k" : 1,
                "/d/beijing/npc/shizhe" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}