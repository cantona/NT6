// xilingqiao.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "西泠橋");
        set("long", @LONG
西泠橋銜結孤山，跨過裡西湖。橋的東南邊是孤山。北邊則是一
條青石大道。
LONG);
        set("exits", ([
            "southeast" : __DIR__"gushan",
            "north"     : __DIR__"road7",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 800);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}