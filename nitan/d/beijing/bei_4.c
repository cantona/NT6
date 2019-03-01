#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西單北大街");
        set("long", @LONG
這裡是北京城的西單北大街，寬闊的大道向南北走向延伸。街道
上的行人接踵而至，市井的喧嘩聲、官兵的馬蹄聲以及小商小販的吆
喝聲不斷，魚龍混雜其中，很是熱鬧。北方通往地西大街。
LONG );
       set("exits", ([
                "west" : "/d/beijing/bei_3",
                "north" : "/d/beijing/di_1",
                "south" : "/d/beijing/bei_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/youren" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}