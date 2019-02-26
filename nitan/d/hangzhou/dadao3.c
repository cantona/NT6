// dadao3.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "沿湖大道");
        set("long", @LONG
一條寬敞的大道上卻遊人稀少。原來這裏沿路住着的都是達官貴
人。本來風景秀麗之處，卻顯的一片蕭瑟。路的西邊是一座莊園，大
道向南北延伸。
LONG);
        set("exits", ([
            "south"     : __DIR__"road19",
            "north"     : __DIR__"dalu1",
            "west"      : __DIR__"liuzhuang",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xihu");
	set("coor/x", 780);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
}