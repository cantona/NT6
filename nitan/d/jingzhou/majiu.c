#include <room.h>
inherit TRANS_ROOM;

void create()
{
        set("short", "馬廄");
        set("long", @LONG
這是客店後的馬廄，常年供應着新鮮的草料。荊州城民風淳樸，
馬伕們會把馬牽到馬廄好生照看，將它們餵飽飲足，再洗刷得幹乾淨
淨，一直伺候到客人上路。馬廄雨檐下的爛木柱上釘着一塊破木牌 (
paizi)。馬廄中堆放著幾堆草料。
LONG );
        set("outdoors", "jinzhou");
        set("no_fight", 1);
        set("objects", ([
              "/clone/horse/zaohongma": 1,
              "/clone/horse/huangbiaoma": 1,
              "/clone/horse/ziliuma": 1,
              "/clone/npc/mafu": 1,
        ]));
        set("exits",([
                "west" : __DIR__"kedian",
                "up"   : "/clone/shop/jingzhou_shop",
        ]));
        set("coor/x", -7080);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}