#include <room.h>
inherit ROOM;

void create()
{
        set("short", "韋府走廊");
        set("long", @LONG
這是一條木製的走廊，地面很是光滑，被打整得一塵不染。幾個
韋府的下人在此走動。北邊是個巨大的花園。
LONG );
       set("exits", ([
                "north" : "/d/beijing/weifu_dayuan",
                "east" : "/d/beijing/weifu_men",
        ]));
        set("objects", ([
                "/d/beijing/npc/shizhe" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}