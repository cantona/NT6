#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "城門口");
        set("long", @LONG
這裏是京城西城城邊靠近城門的一條寬闊的大道，西方就是京城
的西城門了，厚實堅固的古城牆高高聳立着。每天都有許多人經過這
條大道出入京城。東方是京城的西單北大街。
LONG );
        set("exits", ([
                "west" : "/d/beijing/xichengmen",
                "east" : "/d/beijing/bei_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/tiaofu" : 1,
                "/d/beijing/npc/old2" : 1,
                "/d/beijing/npc/tangzi" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}