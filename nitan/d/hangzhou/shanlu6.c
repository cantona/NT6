// shanlu6.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit BUILD_ROOM;
void create()
{
        set("short", "山路");
        set("long", @LONG
山路崎嶇，曲折蜿延。四周林木蒼翠，修竹茂密。山路旁有一山
洞，據説洞裏有時會傳出虎哮聲，故名老虎洞。西邊是下山的路，往
東下山便到了山底。
LONG);
        set("exits", ([
            "eastup"  : __DIR__"yuhuangsd",
            "westdown": __DIR__"yuhuangshan",
        ]));
        set("objects", ([
            __DIR__"npc/laohu" : 1,
            __DIR__"obj/shuzhi" : 1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 770);
	set("coor/y", -2100);
	set("coor/z", 10);
	setup();
}
