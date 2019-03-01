// This program is a part of NT MudLIB

#include <room.h>
inherit TRANS_ROOM;

void create()
{
        set("short","馬廄");
        set("long",@LONG
這是南陽城的馬廄，常年供應新鮮草料。南陽地處中原，來往的行人
絡繹不絕。馬廄雨檐下的爛木柱上釘著一塊破木牌(paizi)。
    馬廄中堆放著幾堆草料，正中有一口泔槽。
LONG);
        set("outdoors", "nanyang");
        set("region", "nanyang");
        set("no_fight", 1);
        set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
                "west" : __DIR__"kedian1",
        ]));

	set("coor/x", -6920);
	set("coor/y", 770);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}