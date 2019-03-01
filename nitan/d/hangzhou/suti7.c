// suti7.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "蘇堤");
        set("long", @LONG
蘇堤是詩人蘇東坡在主持濬深西湖時用湖泥和草築成的。蘇東坡
曾有詩記述此事；“我在錢塘拓湖淥，大堤士女爭昌豐。六橋橫絕天
漢上，北山始與南屏通。忽驚二十五萬丈，老葑席卷蒼煙空。”往南
便是大道，北邊是映波橋。映波橋乃蘇堤六橋由至北南的第一座。
LONG);
        set("exits", ([
            "north"     : __DIR__"suti6",
            "south"     : __DIR__"road20",
        ]));
        set("objects", ([
            __DIR__"npc/shu-sheng" : 1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 790);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}