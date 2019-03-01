// road6.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上遊人，或步行，或乘轎，或騎馬。個個喜氣洋洋的來遊西
湖。大道延伸向東西兩邊。南邊則通往蘇堤。北邊是岳王廟。
LONG);
        set("exits", ([
            "north"     : __DIR__"yuelang",
            "south"     : __DIR__"suti1",
            "west"      : __DIR__"road5",
            "east"      : __DIR__"road7",
        ]));
        set("objects" , ([
            __DIR__"npc/liumang" :4,
            __DIR__"npc/liumangtou" :1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 790);
	set("coor/y", -2010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}