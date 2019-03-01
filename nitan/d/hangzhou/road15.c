// road15.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上游人，或步行，或乘轎，或騎馬。個個喜氣洋洋的來遊西
湖。東北和西邊各是一條大道。西南邊是上玉皇山的山路。
LONG);
        set("exits", ([
            "northeast" : __DIR__"road14",
            "southwest" : __DIR__"yuhuangsj",
            "west"      : __DIR__"road16",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xihu");
	set("coor/x", 810);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}