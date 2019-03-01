// road3.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道兩邊遍植青松，滿目蒼翠，偃蓋如雪。被稱為“九里雪松”。
東北邊是洪春橋。再向西南便到了靈隱寺。南邊是一條土路。
LONG);
        set("exits", ([
            "southup"     : __DIR__"huangniling",
            "southwest"   : __DIR__"road2",
            "northeast"   : __DIR__"hongchunqiao",
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
	set("coor/x", 760);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}