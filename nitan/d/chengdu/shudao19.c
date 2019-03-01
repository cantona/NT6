#include <ansi.h>
#include <room.h>
inherit BUNCH_ROOM;

void create()
{
        set("short", "官道");
        set("long", @LONG
你走在一條官道上，西面已經可以隱約看見成都城的城門了，東
去是蜀道。
LONG );
        set("exits", ([
                "west" :  __DIR__"road2",
                "east" : __DIR__"shudao18",
        ]));
        set("objects", ([
                "/d/beijing/npc/shusheng2" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -15160);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
}
