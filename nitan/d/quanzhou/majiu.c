// Room: /d/quanzhou/majiu.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "馬廄");
        set("long", @LONG
這是客棧邊上的馬廄，常年供應新鮮草料。據説此地民風淳樸，客
人只要住店，馬伕們就會把馬牽到馬廄好生照看，將它們餵飽飲足，再
洗刷得幹乾淨淨。一直伺候到客人離店上路。馬廄中堆放著幾堆草料，
正中有一口泔槽。馬廄雨檐下的爛木柱上釘着一塊破木牌(paizi)。
LONG );
        set("outdoors", "quanzhou");
        set("item_desc", ([
                "paizi" :
"客人們只要給馬伕一兩白銀的租金就可以僱到一匹馬了。

前往      福州城:  ridefz
"
        ]));
        set("exits", ([
                "south" : __DIR__"kedian",
                "up"    : SHOP_DIR"quanzhou_shop",
        ]));
        set("objects", ([
                "/clone/misc/mafu" : 1,
                "/d/city/npc/ziliuma" : 1,
                "/d/city/npc/zaohongma" : 1,
                "/d/city/npc/huangbiaoma" : 1,
        ]));
	set("coor/x", -890);
	set("coor/y", -7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}