// dadao2.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "沿湖大道");
        set("long", @LONG
一條寬敞的大道上卻遊人稀少。原來這裡沿路住著的都是達官貴
人。本來風景秀麗之處，卻顯的一片蕭瑟。大道向西南和北延伸。
LONG);
        set("exits", ([
            "north"     : __DIR__"dadao1",
            "southwest" : __DIR__"dalu1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xihu");
	set("coor/x", 790);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
}