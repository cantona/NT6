// road18.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上遊人，或步行，或乘轎，或騎馬。個個喜氣洋洋的來遊西
湖。大道伸向東北和南兩邊，往西是石屋洞。
LONG);
        set("exits", ([
            "northeast" : __DIR__"road19",
            "west"      : __DIR__"shiwudong",
            "south"     : __DIR__"road17",
            "east"      : __DIR__"yuhuangshan",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 770);
	set("coor/y", -2100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}