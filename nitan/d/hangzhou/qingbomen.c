// qingbomen.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "清波門");
        set("long", @LONG
園門口有一大門樓，大匾上刻着“清波門”。門樓下站着幾個嬉
嬉哈哈的少女，惹人墜步相觀。再往西就進了聚景園，往東便回到大
路。
LONG);
        set("exits", ([
            "east"   : __DIR__"road14",
            "west"   : __DIR__"jujingyuan",
        ]));
        set("objects", ([
            __DIR__"npc/girl" : 2,
        ]));
        set("outdoors", "xihu");
//        set("no_clean_up", 0);
	set("coor/x", 810);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}