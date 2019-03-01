// fajingsi.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "法鏡寺");
        set("long", @LONG
法鏡寺建在小溪旁，格外的幽雅。進香的遊客不時的進進出出。
南上往中天竺。朝北是下山的路。
LONG);
        set("exits", ([
                "southup"   : __DIR__"shanlu2",
                "northdown" : __DIR__"shanlu1",
        ]));
        set("objects", ([
           __DIR__"npc/shami" : 1,
           __DIR__"npc/guest" : 1,
        ]));
        set("outdoors", "hangzhou");
	set("coor/x", 750);
	set("coor/y", -2070);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}