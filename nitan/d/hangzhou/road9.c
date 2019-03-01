// road9.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上游人，或步行，或乘轎，或騎馬。個個喜氣洋洋的來遊西
湖。大道延伸向西邊。斷橋在大道的西南邊。南邊則是另一條大道。
LONG);
        set("exits", ([
            "west"      : __DIR__"road8",
            "south"     : __DIR__"road10",
            "southwest" : __DIR__"duanqiao",
            "northeast" : __DIR__"matou",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 820);
	set("coor/y", -2000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}