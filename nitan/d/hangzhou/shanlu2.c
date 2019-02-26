// shanlu2.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit BUILD_ROOM;
void create()
{
        set("short", "山路");
        set("long", @LONG
走在這條不是很寬的山路上，只見兩旁峯巒秀麗，景色怡人。一
條小溪在路邊潺潺流過，溪畔有一農家。山村小景，使人有退隱江湖
之意。南上便到了中天竺。北下就是下天竺。
LONG);
        set("exits", ([
            "southup"   : __DIR__"fajinsi",
            "northdown" : __DIR__"fajingsi",
        ]));
        set("objects", ([
            __DIR__"npc/honghua2" : 2,
        ]));
        set("outdoors", "hangzhou");
	set("coor/x", 750);
	set("coor/y", -2080);
	set("coor/z", 30);
	setup();
}
