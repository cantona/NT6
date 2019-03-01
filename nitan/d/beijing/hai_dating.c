inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","海澄公府大廳");
        set("long", @LONG
這是海澄公府的大廳，大廳不大，裝飾也不華麗，很難想象這裡
竟然是一等公爵的居所。此時大廳內外一片嘈雜，擠滿了上門來尋事
的御前侍衛。
LONG );
        set("exits", ([
                "north" : "/d/beijing/hai_dayuan",
                "south" : "/d/beijing/hai_houyuan",
        ]));
        set("objects", ([
                "/d/beijing/npc/duolong" : 1,
                "/d/beijing/npc/zheng" : 1,
                "/d/beijing/npc/feng" : 1,
        ]));

	set("coor/x", -2810);
	set("coor/y", 7620);
	set("coor/z", 0);
	setup();
}