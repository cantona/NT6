// road7.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上游人，或步行，或乘轎，或騎馬。個個喜氣洋洋的來遊西
湖。大道延伸向西邊和東北邊。朝北走便是上北山。南邊則通往西泠
橋。
LONG);
        set("exits", ([
            "northeast" : __DIR__"road8",
            "north"     : __DIR__"shanlu8",
            "south"     : __DIR__"xilingqiao",
            "west"      : __DIR__"road6",
        ]));
        set("objects", ([
            __DIR__"npc/youfang" : 1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 800);
	set("coor/y", -2010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}