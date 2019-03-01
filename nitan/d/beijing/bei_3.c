#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西單北大街");
        set("long", @LONG
這裡是北京城的西單北大街，寬闊的大道向南北走向延伸。街道
上的行人接踵而至，市井的喧嘩聲、官兵的馬蹄聲以及小商小販的吆
喝聲不斷，魚龍混雜其中，很是熱鬧。西邊是熱鬧的北街菜市，北方
就是西四北大街了。
LONG );
       set("exits", ([
                "east" : "/d/beijing/bei_4",
                "west" : "/d/beijing/caishi",
                "north" : "/d/beijing/shi_1",
                "south" : "/d/beijing/bei_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/girl3" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}