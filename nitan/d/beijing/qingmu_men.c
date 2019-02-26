#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青木堂大門");
        set("long", @LONG
這是一個很普通的四合院，破舊的大門敞開着，大門裏是一個大
院，院子四周是幾間普通的民居。
LONG );
       set("exits", ([
                "north" : "/d/beijing/yangliu3",
                "south" : "/d/beijing/qingmu_dayuan",
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7630);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}