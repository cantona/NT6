#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西單");
        set("long", @LONG
這裏就是西單，西單也是京城裏的繁華地段。人來人往，十分熱
鬧。從南邊揚起了一陣陣馬蹄聲，那是京城的長安大街。西方是一個
鳥市，那是專門為江洲城裏的公子哥兒開設的。北邊不遠就是西單北
大街了。
LONG );
       set("exits", ([
                "east" : "/d/beijing/xi_2",
                "west" : "/d/beijing/niaoshi",
                "north" : "/d/beijing/bei_1",
                "south" : "/d/beijing/caroad_w1",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy1" : 1,
                "/d/beijing/npc/tiaofu" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}