// yuelang.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "岳廊");
        set("long", @LONG
岳王廟的匾上是“心昭天日”四個大字。步入大殿，正中是岳飛
的塑像，身後的匾上題著“還我河山”。北邊的門通向岳墳，往南是
出去的路。
LONG);
        set("exits", ([
            "north"     : __DIR__"yuefen",
            "south"     : __DIR__"road6",
        ]));
        set("objects" , ([
            "/d/mingjiao/npc/chengchaofeng" : 1,
            __DIR__"npc/honghua2" :2,
        ]));
//        set("no_clean_up", 0);
	set("coor/x", 790);
	set("coor/y", -2000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}