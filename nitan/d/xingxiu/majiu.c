//Room: majiu1.c 馬廄
//Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
        set("short","馬廄");
        set("long",@LONG
這是北疆小鎮的馬廄，常年供應新鮮草料。這裏地處會疆，邊民古
樸而好客，把所有遠方來賓均作兄弟看待。馬伕們會把馬牽到馬廄好生
照看，將它們餵飽飲足，再梳理得清清爽爽，一直伺候到客人上路。馬
廄舊木柱上釘着一塊破木牌(paizi)。
    馬廄中堆放著幾堆草料，正中有一口泔槽。
LONG);
        set("no_fight", "1");
        set("no_beg", "1");
        set("objects", ([
                "/d/city/npc/zaohongma": 1,
                "/d/city/npc/huangbiaoma": 1,
                "/d/city/npc/ziliuma": 1,
                "/d/city/npc/camel": 1,
                "/clone/misc/mafu": 1,
        ]));
        set("item_desc", ([
                "paizi": @TEXT
客人們只要給馬伕一兩白銀的租金就可以僱到一匹馬了。

前往      長安城:  rideca


TEXT]));
        set("exits",([ /* sizeof() == 1 */
                "west" : __DIR__"kezhan",
                "up"   : SHOP_DIR"yili_shop",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -38990);
        set("coor/y", 13100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}