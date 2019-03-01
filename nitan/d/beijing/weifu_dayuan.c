#include <room.h>
inherit ROOM;

void create()
{
        set("short", "韋府大院");
        set("long", @LONG
這是鹿鼎公府正廳前面的一個寬闊的大院，大院裡種植著各類花
草，假山水池，瓊樓高台，非常豪華。院內打掃得非常幹凈，韋府裡
的下人穿梭其中，北邊是一條木制走廊，通往康府的大廳。
LONG );
       set("exits", ([
                "south" : "/d/beijing/weifu_zoulang1",
                "north" : "/d/beijing/weifu_zoulang2",
        ]));
        set("objects", ([
                "/d/beijing/npc/yuanding" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}