// suti4.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "蘇堤");
        set("long", @LONG
春曉，漫步林蔭道上，煙柳籠紗，雀鳥歡鳴，一片生機。蘇堤春
曉被列為西湖十景之首，果然名不虛傳。北邊是壓堤橋，南面是望山
橋。東面一片梅林，林後似乎有座院落，但看不真切。
LONG);
        set("exits", ([
            "north"     : __DIR__"suti3",
            "south"     : __DIR__"suti5",
        ]));
        set("objects", ([
            __DIR__"npc/liyuanzhi" : 1,
            __DIR__"npc/wuya" : 1,
            __DIR__"npc/maque" : 2,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 790);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}