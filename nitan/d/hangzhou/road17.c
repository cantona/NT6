// road17.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上游人，或步行，或乘轎，或騎馬。個個喜氣洋洋的來遊西
湖。大道伸向南北兩邊，往西是虎跑泉，往東是一條山路。
LONG);
        set("exits", ([
            "north"     : __DIR__"road18",
            "south"     : __DIR__"qiantang",
            "west"      : __DIR__"hupaoquan",
            "east"      : __DIR__"kslu",
        ]));
        set("objects", ([
            __DIR__"npc/tiao-fu" : 1,
            __DIR__"npc/chuyuan" : 1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 770);
	set("coor/y", -2110);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}