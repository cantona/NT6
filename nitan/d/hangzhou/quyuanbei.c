// quyuanbei.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "曲院風荷");
        set("long", @LONG
跨過小拱橋，迎面有一亭院，旁邊立著石碑，上題“曲院風荷。”
往東是回蘇堤。
LONG);
        set("exits", ([
            "east"     : __DIR__"suti2",
            "enter"    : __DIR__"quyuanfenghe",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 780);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}