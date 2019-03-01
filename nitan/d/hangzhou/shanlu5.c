// shanlu5.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit BUILD_ROOM;
void create()
{
        set("short", "山路");
        set("long", @LONG
走在小路上，只見漫山遍野都是綠油油的茶蓬。農家少女們在歡
笑聲中採茶。山路延伸向東西兩邊，北邊就是龍井，東北邊有一條土
路。
LONG);
        set("exits", ([
                "westup"   : __DIR__"shanlu4",
                "northeast": __DIR__"tulu1",
                "north"    : __DIR__"longjing",
                "east"     : __DIR__"yanxiadong",
        ]));
        set("objects", ([
                __DIR__"npc/caichanu" :2,
        ]));
        set("outdoors", "hangzhou");
	set("coor/x", 770);
	set("coor/y", -2110);
	set("coor/z", 40);
	setup();
}
