#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西單北大街");
        set("long", @LONG
這裏是北京城的西單北大街，寬闊的大道向南北走向延伸。街道
上的行人接踵而至，市井的喧譁聲、官兵的馬蹄聲以及小商小販的吆
喝聲不斷，魚龍混雜其中，很是熱鬧。西邊的街道通西城門。
LONG );
       set("exits", ([
                "east" : "/d/beijing/bei_2",
                "west" : "/d/beijing/ximenkou",
                "north" : "/d/beijing/bei_3",
                "south" : "/d/beijing/xi_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/youren" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}