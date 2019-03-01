// shenxudong.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "射旭洞");
        set("long", @LONG
洞後側穹頂上的石罅間可仰見一束天光，故又名“一線天”。東
南邊是下山的路。
LONG);
        set("exits", ([
                "southeast" : __DIR__"longhongdong",
        ]));
        set("objects", ([
             __DIR__"npc/mengmian":1,
        ]));
        set("outdoors", "hangzhou");
	set("coor/x", 720);
	set("coor/y", -2060);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}