// road19.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上遊人，或步行，或乘轎，或騎馬。個個喜氣洋洋的來遊西
湖。大道伸向東和西南兩邊，往北是另一條大道。
LONG);
        set("exits", ([
            "north"     : __DIR__"dadao3",
            "southwest" : __DIR__"road18",
            "east"      : __DIR__"road20",
        ]));
        set("objects" , ([
            __DIR__"npc/dao-ke"  :1,
            __DIR__"npc/longjun" :1,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 780);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}