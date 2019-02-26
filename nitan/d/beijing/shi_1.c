#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西四北大街");
        set("long", @LONG
這裏是京城的西四南大街，青石鋪砌道路貫通南北，著名的磚塔
兒衚衕也在這條大街上。街道上的行人熙熙攘攘。南方接京城的西單
北大街，北方是西四北大街。
LONG );
       set("exits", ([
                "north" : "/d/beijing/shi_2",
                "south" : "/d/beijing/bei_3",
                "west" : "/d/beijing/minju",
        ]));
        set("objects", ([
                "/d/beijing/npc/liumang" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}