#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西單北大街");
        set("long", @LONG
這裡是北京城的西單北大街，寬闊的大道向南北走向延伸。街道
上的行人接踵而至，市井的喧嘩聲、官兵的馬蹄聲以及小商小販的吆
喝聲不斷，魚龍混雜其中，很是熱鬧。往西走的通西城門，東邊是一
座富麗堂皇的建築，門額上懸掛一方橫匾，寫著『康親王府』四個大
字。
LONG );
       set("exits", ([
                "east" : "/d/beijing/kangfu_men",
                "west" : "/d/beijing/bei_1",
                "north" : "/d/beijing/bei_4",
                "south" : "/d/beijing/xi_2",
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}