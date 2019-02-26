// Room: /d/yanping/majiu.c
// Date: May,31 1998 Java

inherit ROOM;

void create()
{
        set("short","馬廄");
        set("long",@LONG
這是延平城的馬廄，常年供應新鮮草料。延平城民風淳樸，馬伕們
會把馬牽到馬廄好生照看，將它們餵飽飲足，再洗刷得幹乾淨淨，一直
伺候到客人上路。馬廄雨檐下的爛木柱上釘着一塊破木牌(paizi)。
    馬廄中堆放著幾堆草料，正中有一口泔槽。
LONG);
        set("outdoors", "fuzhou");
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
客人們只要給馬伕一兩白銀的租金就可以僱到一匹馬了。

前往      揚州城:  rideyz

TEXT]));
        set("exits",([ /* sizeof() == 1 */
                "south" : __DIR__"mazhan",
                "up"    : SHOP_DIR"yanping_shop",
        ]));
        set("coor/x", 1850);
        set("coor/y", -6280);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}