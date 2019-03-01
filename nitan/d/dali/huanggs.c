// Room : /d/dali/huanggs.c 黃果樹瀑布

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "黃果樹瀑布");
        set("long", @LONG
這兒是大理聞名于天下的黃果樹瀑布，河流縱橫交錯，瀑布成群，
洞穴成串，峰巒疊翠，植被奇特，呈現出層次豐富的喀斯特山水旖旎
風光。
LONG );
        set("outdoors", "dali");

        set("exits", ([
                "east" : __DIR__"feilihusouth",
        ]));
	set("coor/x", -19140);
	set("coor/y", -6970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}