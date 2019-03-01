// suti5.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "蘇堤");
        set("long", @LONG
每當盛夏，遊客到此紛紛尋蔭小息，堤上綠樹交柯，鳴蟬噪鼓。
北邊是望山橋，南面鎖瀾橋。
LONG);
        set("exits", ([
            "north"     : __DIR__"suti4",
            "south"     : __DIR__"suti6",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 790);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}