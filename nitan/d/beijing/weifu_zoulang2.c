#include <room.h>
inherit ROOM;

void create()
{
        set("short", "韋府走廊");
        set("long", @LONG
這是一條木制的走廊，地面很是光滑，被打整得一塵不染。幾個
韋府的下人在此走動。南邊是個巨大的花園，北邊就是韋府的大廳。
LONG );
       set("exits", ([
                "north" : "/d/beijing/weifu_dating",
                "south" : "/d/beijing/weifu_dayuan",
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}