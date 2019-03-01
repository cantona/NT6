// road2.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上遊人，或步行，或乘轎，或騎馬。個個喜氣洋洋的來遊西
邊是靈隱寺和飛來峰。往南是上天竺。
LONG);
        set("exits", ([
                "southup"   : __DIR__"shanlu1",
                "southwest" : __DIR__"road1",
                "northeast" : __DIR__"road3",
        ]));
        set("objects", ([
           __DIR__"npc/xianghuo" : 1,
        ]));
        set("outdoors", "hangzhou");
	set("coor/x", 750);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}