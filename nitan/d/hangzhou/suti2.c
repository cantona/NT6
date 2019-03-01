// suti2.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "蘇堤");
        set("long", @LONG
蘇堤上，遊客們有的林蔭大道上漫步吟詩，高談闊論；有的隨機
就石，臨水而坐；有的伶立湖邊，靜享湖景。北邊是跨虹橋，南面是
東浦橋，西面是去曲院風荷。
LONG);
        set("exits", ([
            "north"     : __DIR__"suti1",
            "south"     : __DIR__"suti3",
            "west"      : __DIR__"quyuanbei",
        ]));
        set("objects", ([
                "/clone/medicine/vegetable/heye" : random(2),
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 790);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}