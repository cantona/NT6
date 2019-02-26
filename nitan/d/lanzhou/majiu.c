#include <room.h>
inherit TRANS_ROOM;

void create()
{
        set("short","馬廄");
        set("long", @LONG
這是順風客棧後的馬廄，常年供應新鮮草料。蘭州民風淳樸，馬
夫們會把馬牽到馬廄好生照看，將它們餵飽飲足，再洗刷得幹乾淨淨，
一直伺候到客人上路。馬廄雨檐下的爛木柱上釘着一塊破木牌 (paiz
i)。馬廄中堆放著幾堆草料，正中有一口泔槽。
LONG );
        set("outdoors", "lanzhou");
        set("no_fight", 1);
        set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
        ]));
        set("exits",([
                "north"  : __DIR__"kedian",
        ]));
	set("coor/x", -15740);
	set("coor/y", 3790);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}