inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","海澄公府大院");
        set("long", @LONG
這是進門後的一個不大的花園。西面是一個廂房，東面是一扇月
形門通往海澄公府的花廳，北面是海澄公府的大門，南面就是大廳了。
LONG );
        set("exits", ([
                "north" : "/d/beijing/hai_men",
                "south" : "/d/beijing/hai_dating",
                "east" : "/d/beijing/hai_huating",
                "west" : "/d/beijing/hai_fang",
        ]));
        set("objects", ([
                "/d/beijing/npc/yuqian1" : 1,
                "/d/beijing/npc/yuqian2" : 1,
        ]));

	set("coor/x", -2810);
	set("coor/y", 7630);
	set("coor/z", 0);
	setup();
}