// huanglongdong.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "黃龍洞");
        set("long", @LONG
一進山門，松篁交翠，別有洞天。石壁陡削，苔痕常綠；迴廊臨
之間有一小峯，上題：“有龍則靈”。
LONG);
        set("exits", ([
            "south"     : __DIR__"shanlu8",
        ]));
        set("objects", ([
            __DIR__"npc/dushe" : 1,
        ]));
//        set("no_clean_up", 0);
	set("coor/x", 800);
	set("coor/y", -1990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}