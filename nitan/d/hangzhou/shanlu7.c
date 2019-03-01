// shanlu7.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit BUILD_ROOM;
void create()
{
        set("short", "山路");
        set("long", @LONG
山路崎嶇，曲折蜿延。四周林木蒼翠，修竹茂密。山路旁是涵碧
亭，在這裡極目遠眺，群山環湖盡收眼底。西邊是上山的路，往東便
是下山的路。
LONG);
        set("exits", ([
            "eastdown": __DIR__"yuhuangsj",
            "westup"  : __DIR__"yuhuangsd",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 790);
	set("coor/y", -2100);
	set("coor/z", 10);
	setup();
}
