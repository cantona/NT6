// Room: /d/city/jiaowai13.c
// Jan. 8.1998 by Venus
#include <room.h>
inherit ROOM;

void create()
{
    set("short", "密林");
        set("long", @LONG
揚州郊外的茂密樹林，陰森可怖。抬頭不見天日。這裏也是揚州
命案發生最多的地方。鳥獸蛇蟲遊蕩不窮。
LONG );
    set("exits", ([
        "south" : "/d/city/jiaowai11",
        "east"  : "/d/city/jiaowai12",
    ]));
    set("objects", ([
        CLASS_D("gaibang")+"/mo-bu" : 1,
        "/d/city/obj/shuzhi": 1,
    ]));
//    set("no_clean_up", 0);
	set("coor/x", -40);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
    replace_program(ROOM);
}