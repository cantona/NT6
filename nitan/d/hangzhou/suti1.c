// suti1.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "蘇堤");
        set("long", @LONG
蘇堤是詩人蘇東坡在主持浚深西湖時用湖泥和草築成的。蘇東坡
曾有詩記述此事；“我在錢塘拓湖淥，大堤士女爭昌豐。六橋橫絕天
漢上，北山始與南屏通。忽驚二十五萬丈，老葑席捲蒼煙空。”往北
便是大道，南邊是跨虹橋。跨虹橋乃蘇堤六橋由北至南的第一座。橋
一邊是嶽湖，橋的另一邊是西湖。
LONG);
        set("exits", ([
            "north"     : __DIR__"road6",
            "south"     : __DIR__"suti2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xihu");
	set("coor/x", 790);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}