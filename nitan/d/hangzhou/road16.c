// road16.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上游人，或步行，或乘轎，或騎馬。個個喜氣洋洋的來遊西
湖。北邊可上雷峯，南邊是淨慈寺。
LONG);
        set("exits", ([
            "northup" : __DIR__"xizhaoshan",
            "south"   : __DIR__"jingcisi",
            "east"    : __DIR__"road15",
            "west"    : __DIR__"road20",
        ]));
        set("objects", ([
            __DIR__"npc/baizhen" : 1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 800);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}