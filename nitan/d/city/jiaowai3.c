// Room: /d/city/jiaowai3.c
// Jan. 8.1998 by Venus
#include <room.h>
inherit ROOM;

void create()
{
    set("short", "樹林");
        set("long", @LONG
揚州郊外的樹林，松枝挺拔，喬木橫斜。林間小道，逶迤隨遠。
林中蟬鳴廝鬧，鳥啼宛轉，使你頓時煩意盡消。    地上落了很多樹
枝石塊。
LONG );
    set("exits", ([
        "north" : "/d/city/jiaowai2",
        "south" : "/d/city/jiaowai4",
    ]));
    set("objects", ([
        "/d/city/obj/shitou": 2,
    ]));
//    set("no_clean_up", 0);
    set("outdoors", "yangzhou");
	set("coor/x", 40);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();
    replace_program(ROOM);
}