// suti3.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "蘇堤");
        set("long", @LONG
寒冬，瑞雪霏霏中，不少遊人踏雪觀景。從堤上極目遠眺，只見
四周玉樹瓊林。北邊是東浦橋，南面是壓堤橋。
LONG);
        set("exits", ([
            "north"     : __DIR__"suti2",
            "south"     : __DIR__"suti4",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xihu");
	set("coor/x", 790);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}