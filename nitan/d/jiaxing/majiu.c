#include <room.h>
inherit TRANS_ROOM;

void create()
{
        set("short","馬廄");
        set("long", @LONG
這是嘉興城的馬廄，常年供應新鮮草料。馬廄雨檐下的爛木柱上
釘著一塊破木牌(paizi)。    
    馬廄中堆放著幾堆草料，正中有一口泔槽。
LONG );
        set("outdoors", "jiaxing");
        set("no_fight", 1);
        set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
                "northeast" : __DIR__"jxnanmen",
        ]));
	set("coor/x", 1180);
	set("coor/y", -1790);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}