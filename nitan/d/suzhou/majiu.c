// Room: /d/suzhou/majiu.c
// Date: May,31 1998 Java

#include <room.h>
inherit TRANS_ROOM; 

void create()
{
        set("short","馬廄");
        set("long",@LONG
這是北大街的馬廄，常年供應新鮮草料。蘇州民風淳樸，馬夫們會
把馬牽到馬廄好生照看，將它們喂飽飲足，再洗刷得幹乾凈凈，一直伺
候到客人上路。馬廄雨檐下的爛木柱上釘著一塊破木牌(paizi)。
    馬廄中堆放著幾堆草料，正中有一口泔槽。
LONG);
        set("outdoors", "suzhou");
        set("no_fight", "1");
        set("no_beg", "1");
        set("no_clean_up", 0);
        set("objects", ([
                "/d/city/npc/zaohongma": 1,
                "/d/city/npc/huangbiaoma": 1,
                "/d/city/npc/ziliuma": 1,
                "/clone/misc/mafu": 1,
        ]));
        set("item_desc", ([
                "paizi": @TEXT
客人們只要給馬夫一兩白銀的租金就可以雇到一匹馬了。

前往      揚州城:  rideyz

TEXT]));
        set("exits",([ /* sizeof() == 1 */
                "east"  : __DIR__"beidajie1",
                "south" : __DIR__"xiyuan",
                "north" : __DIR__"business",
                "up"    : SHOP_DIR"suzhou_shop",
        ]));
	set("coor/x", 1100);
	set("coor/y", -1040);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}