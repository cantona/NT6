// chashi.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "茶室");
        set("long", @LONG
這裏是龍井茶茶室。在這裏可以品到最新鮮的龍井。
LONG);
        set("exits", ([
                "west"     : __DIR__"longjing",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 780);
	set("coor/y", -2100);
	set("coor/z", 40);
	setup();
        replace_program(ROOM);
}