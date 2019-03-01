// road1.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上擠滿了來靈隱寺上香和上飛來峰的遊客。北邊過了小溪就
是靈隱寺了。南邊是上飛來峰的路。
LONG);
        set("exits", ([
                "northwest" : "/d/jiaxing/jxnanmen",
                "northeast" : __DIR__"road2",
                "north"     : __DIR__"lingyinsi",
                "south"     : __DIR__"feilaifeng",
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
	set("coor/x", 740);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}