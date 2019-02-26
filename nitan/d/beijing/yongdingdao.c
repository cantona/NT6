#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "大道");
        set("long", @LONG
這裏是紫禁城北邊靠近城門的一條寬闊的大道，南方不遠就是京
城的永定門了，厚實堅固的古城牆高高聳立着。每天都有許多人經過
這條大道出入京城。北方則經過天壇通往京城的中心。東面則是無極
幫的北京分舵。
LONG );
        set("exits", ([
                "north" : "/d/beijing/tiantan",
                "south" : "/d/beijing/yongdingmen",
        "east" : "/d/beijing/wjb_bjwfb",
        ]));
        set("objects", ([
                "/d/beijing/npc/tiaofu" : 1,
                "/d/beijing/npc/kid1" : 1,
                "/d/beijing/npc/tangzi" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7620);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}