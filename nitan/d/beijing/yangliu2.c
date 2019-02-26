#include <room.h>
inherit ROOM;

void create()
{
        set("short", "楊柳衚衕");
        set("long", @LONG
這裏是楊柳衚衕的深處。走到這裏，光線越發的暗淡起來，狹窄
的通道還在不斷的向南邊延伸。
LONG );
       set("exits", ([
                "north" : "/d/beijing/yangliu1",
                "south" : "/d/beijing/yangliu3",
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}