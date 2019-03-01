#include <room.h>
inherit ROOM;

void create()
{
        set("short", "校場");
        set("long", @LONG
這裡是京城兵營東方的一個大校場，校場裡密密麻麻到處都是官
兵，在武將的指揮下列隊操練，一個個官兵生龍活虎，整齊的排列著。
還有些太監在四處走動。東邊是京城裡著名的王府井大街。
LONG );
        set("exits", ([
                "east" : "/d/beijing/wang_3",
        ]));

        set("objects", ([
                "/d/beijing/npc/taijian" : 1,
                "/d/beijing/npc/bing1" : 2,
                "/d/beijing/npc/bing2" : 2,
                "/d/beijing/npc/bing3" : 2,
                "/d/beijing/npc/yuqian1" : 1,
        ]));

	set("coor/x", -2790);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
}