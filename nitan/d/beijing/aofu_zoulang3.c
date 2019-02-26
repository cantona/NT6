#include <room.h>
inherit ROOM;

void create()
{
        set("short", "鰲府走廊");
        set("long", @LONG
一條木製結構的走廊，地面被打整得一塵不染，很是光滑。鰲府
的丫鬟和下人穿梭至其中。西邊是鰲狠的書房，東邊是鰲狠府的後院。
LONG );

        set("exits", ([
                "east" : "/d/beijing/aofu_houyuan",
                "west" : "/d/beijing/aofu_shufang",
        ]));
        set("objects", ([
                "/d/beijing/npc/jiading_a" : 1,
                "/d/beijing/npc/yahuan_a" : 1,
        ]));
	set("coor/x", -2830);
	set("coor/y", 7790);
	set("coor/z", 0);
	setup();
}