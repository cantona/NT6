// Room: /d/city/jiaowai8.c
// Jan. 8.1998 by Venus
#include <room.h>
inherit ROOM;

void create()
{
    set("short", "草地");
        set("long", @LONG
這是揚州郊外的一片芳草地，落英繽紛，蜂歌蝶舞，朝露夕光，
沁人心脾。呼朋喚友開懷歡樂正其時。
LONG );
    set("exits", ([
        "east" : "/d/city/nanmen",
        "west" : "/d/city/jiaowai9",
    ]));
    set("no_clean_up", 0);
    set("outdoors", "yangzhou");
	set("coor/x", -10);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();
    replace_program(ROOM);
}