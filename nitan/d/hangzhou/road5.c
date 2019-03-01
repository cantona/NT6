// road5.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上遊人，或步行，或乘轎，或騎馬。個個喜氣洋洋的來遊西
湖。往西是去玉泉寺的路。大道則延伸向東邊和西南邊。
LONG);
        set("exits", ([
            "southwest" : __DIR__"road4",
            "westup"    : __DIR__"yuquan",
            "south"     : __DIR__"dadao1",
            "east"      : __DIR__"road6",
        ]));
        set("objects" , ([
            __DIR__"npc/honghua1" :1,
            __DIR__"npc/tiao-fu" :1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 780);
	set("coor/y", -2010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}