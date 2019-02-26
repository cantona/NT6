#include <room.h>
inherit TRANS_ROOM;

void create()
{
        set("short", "馬廄");
        set("long", @LONG
這是軍營邊上的馬廄，常年供應新鮮草料。此地民風淳樸客人只
要帶馬來，馬伕們就會把馬牽到馬廄好生照看，將它們餵飽飲足，再
洗刷得幹乾淨淨。一直伺候到客人離城上路。馬廄雨檐下的爛木柱上
釘着塊破木牌(paizi)。
LONG );
        set("exits",([
                "east" : __DIR__"bingying",
                "north"  : __DIR__"business",
                "up"   : "/clone/shop/dali_shop",
        ]));

        set("outdoors", "dali");
        set("no_fight", 1);
        set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
        ]));
	set("coor/x", -19150);
	set("coor/y", -6910);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}