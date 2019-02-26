#include <room.h>
inherit ROOM;

void create()
{
        set("short", "鰲府走廊");
        set("long", @LONG
一條木製結構的走廊，地面被打整得一塵不染，很是光滑。鰲府
的丫鬟和下人穿梭至其中。南邊是鰲府的大門，北邊是一個大花園。
LONG );

        set("exits", ([
                "north" : "/d/beijing/aofu_dayuan",
                "south" : "/d/beijing/aofu_men",
        ]));
        set("objects", ([
                "/d/beijing/npc/yahuan_a" : 1,
        ]));
	set("coor/x", -2820);
	set("coor/y", 7750);
	set("coor/z", 0);
	setup();
}