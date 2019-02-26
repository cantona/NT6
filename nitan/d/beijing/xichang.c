inherit ROOM;
#include <ansi.h>

void create()
{
        set("short",RED"西廠"NOR);
        set("long", @LONG
這裏就是京城的特務機構——西廠。大廳內很是寬闊，這裏警備
深嚴，穿着制服的西廠官兵和太監在這裏來回走動。看來這裏不宜久
留，趕快離開為妙。[2；37；0m
LONG );
        set("exits", ([
                "north" : "/d/beijing/xichang_men",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing3" : 4,
                "/d/beijing/npc/taijian" : 1,
        ]));
        set("no_fight", 0);
	set("coor/x", -2810);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
}