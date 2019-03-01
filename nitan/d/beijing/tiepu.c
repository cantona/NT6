#include <room.h>
inherit ROOM;

void create()
{
        set("short", "打鐵舖");
        set("long", @LONG
這是永內東街的一家簡陋的打鐵舖，中心擺著一個火爐，爐火把
四周照得一片通紅，你一走進去就感到渾身火熱。打鐵舖的牆角堆滿
了已完工和未完工的菜刀、鐵錘、鐵棍、匕首、盔甲等物。一位鐵匠
滿頭大汗揮舞著鐵錘，專心致志地在打鐵。
LONG );
       set("exits", ([
                "north" : "/d/beijing/yong_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/tiehuoji" : 1,
                "/d/beijing/npc/tiejiang" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2780);
	set("coor/y", 7640);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}