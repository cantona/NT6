// huangniling.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "黃泥嶺");
        set("long", @LONG
一條黃土路彎彎曲曲，四周非常的安靜。偶爾才看見些遊人匆匆而過。
南北分別是下山的路。
LONG);
        set("exits", ([
            "southdown"   : __DIR__"maojiabu",
            "northdown"   : __DIR__"road3",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
	set("coor/x", 760);
	set("coor/y", -2050);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}