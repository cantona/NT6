// Room: /d/city/jiaowai11.c
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
        "east"   : "/d/city/jiaowai10",
        "north"  : "/d/city/jiaowai13",
    ]));
    set("objects", ([
        "/clone/beast/dushe" : 2,
        "/d/city/obj/shitou": 1,
    ]));
//    set("no_clean_up", 0);
	set("coor/x", -40);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();
    replace_program(ROOM);
}