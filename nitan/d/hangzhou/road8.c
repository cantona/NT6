// road8.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上游人，或步行，或乘轎，或騎馬。個個喜氣洋洋的來遊西
湖。大道延伸向東邊和西南邊。朝北走便是上寶石山。
LONG);
        set("exits", ([
            "east"      : __DIR__"road9",
            "northup"   : __DIR__"baoshishan",
            "southwest" : __DIR__"road7",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 810);
	set("coor/y", -2000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}