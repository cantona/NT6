#include <room.h>
inherit TRANS_ROOM;

void create()
{
        set("short", "馬廄");
        set("long", @LONG
這是北京城的馬廄，常年供應新鮮草料。北京自古天子腳下，啥
都有規矩，客店也特會伺候人，馬伕們會把馬牽到馬廄好生照看，將
它們餵飽飲足，再洗刷得幹乾淨淨，一直伺候到客人上路。雨檐下的
爛木柱上釘着塊破木牌 (paizi)。馬廄中堆放著幾堆草料，正中有一
口泔槽。
LONG );
        set("outdoors", "beijing");
        set("no_fight", 1);
        set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
                "/d/guanwai/npc/shenke" : 1,
        ]));

        set("exits",([
                "east" : __DIR__"niaoshi",
                "north"  : __DIR__"business",
                "up"   : "/clone/shop/beijing_shop",
        ]));
	set("coor/x", -2850);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}