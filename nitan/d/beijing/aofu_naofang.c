#include <room.h>
inherit ROOM;

void create()
{
        set("short", "鰲府牢房");
        set("long", @LONG
這是一個昏暗的房間，窗户都被釘死。地上放着皮鞭、木棍等刑
具，顯然這是鰲狠私立公堂，審訊人犯的所在。一個書生被捆在牆上，
鮮血淋漓，遍體鱗傷。
LONG );
        set("exits", ([
                "south" :  "/d/beijing/aofu_houyuan",
        ]));
        set("objects", ([
                 "/d/beijing/npc/zhuangyu" : 1,
        ]));

	set("coor/x", -2820);
	set("coor/y", 7800);
	set("coor/z", 0);
	setup();
}