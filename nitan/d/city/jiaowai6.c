// Room: /d/city/jiaowai6.c
// Jan. 8.1998 by Venus
#include <room.h>
inherit ROOM;

void create()
{
    set("short", "樹林");
        set("long", @LONG
揚州郊外的樹林，鬆枝挺拔，喬木橫斜。林間小道，逶迤隨遠。
林中蟬鳴廝鬧，鳥啼宛轉，使你頓時煩意盡消。        地上落了很
多樹枝石塊。
LONG );

    set("exits", ([
        "east" : "/d/city/jiaowai5",
        "west" : "/d/city/jiaowai7",
    ]));
    set("objects", ([
        CLASS_D("gaibang")+"/kuai-huosan" : 1,
        "/d/city/obj/shitou": 2,
    ]));
//    set("no_clean_up", 0);
    set("outdoors", "yangzhou");
	set("coor/x", 20);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();
    replace_program(ROOM);
}