// dalu1.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "大路");
        set("long", @LONG
路的東邊是一座小山。山上鬱鬱葱葱，種滿了樹。山上本是一處
觀賞西湖的好地方，但卻被丁財主佔為私有。大路向東北和南延伸。
LONG);
        set("exits", ([
            "northeast" : __DIR__"dadao2",
            "south"     : __DIR__"dadao3",
        ]));
        set("objects", ([
            __DIR__"npc/tiao-fu": 1,
            __DIR__"npc/honghua1" : 2,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "xihu");
	set("coor/x", 780);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
}