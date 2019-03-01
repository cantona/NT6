#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short","馬廄");
        set("long", @LONG
這是衡陽城南的馬廄，常年供應新鮮草料。衡陽地狹人稀來往行
人也很少。從這裡可以乘馬車到附近的城市，馬廄雨檐下的爛木柱上
釘著一塊破木牌(paizi)。 馬廄中堆放著幾堆草料，正中有一口泔槽。
LONG );
        set("outdoors", "henshan");
        set("no_fight", 1);

        set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
        ]));

        set("exits",([
               "north" : __DIR__"hengyang11",
                "up"   : "/clone/shop/hengyang_shop",
        ]));

	set("coor/x", -6910);
	set("coor/y", -5710);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}