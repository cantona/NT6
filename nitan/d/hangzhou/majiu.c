//Room: majiu1.c 馬廄
//Date: Oct. 2 1997 by That

#include <room.h>
inherit TRANS_ROOM;

void create()
{
        set("short","馬廄");
        set("long",@LONG
這是天外天客店後的馬廄，常年供應新鮮草料。杭州自古號稱天堂，
杭州的客店彙集四海賓客。馬伕們會把馬牽到馬廄好生照看，將它們餵飽
飲足，再洗刷得幹乾淨淨，一直伺候到客人上路。馬廄雨檐下的爛木柱上
釘着一塊破木牌(paizi)。
    馬廄中堆放著幾堆草料，正中有一口泔槽。
LONG);
        set("outdoors", "xihu"); 
        set("no_fight", "1");
        set("no_beg", "1");
        set("objects", ([
                "/d/city/npc/zaohongma": 1,
                "/d/city/npc/huangbiaoma": 1,
                "/d/city/npc/ziliuma": 1,
                "/clone/misc/mafu": 1,
        ]));
        set("item_desc", ([
                "paizi": @TEXT
客人們只要給馬伕一兩白銀的租金就可以僱到一匹馬了。

前往        揚州城:  rideyz


TEXT]));
        set("exits",([ /* sizeof() == 1 */
                "west" : __DIR__"kedian",
                "north" : __DIR__"business",
                "up"   : SHOP_DIR"hangzhou_shop",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 850);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}