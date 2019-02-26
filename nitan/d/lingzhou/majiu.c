//Room: majiu.c 馬廄
//Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
        set("short","馬廄");
        set("long",@LONG
這是車馬店邊上的馬廄，常年供應新鮮草料。據説此地民風淳樸，
客人只要住店，馬伕們就會把馬牽到馬廄好生照看，將它們餵飽飲足，
再洗刷得幹乾淨淨。一直伺候到客人離店上路。馬廄中堆放著幾堆草料，
正中有一口泔槽。馬廄雨檐下的爛木柱上釘着一塊破木牌(paizi)。
LONG);
        set("outdoors", "lingzhou");
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

前往      永登城:  rideyd

TEXT]));
        set("exits",([ /* sizeof() == 1 */
                "west" : __DIR__"chema",
                "up"   : SHOP_DIR"lingzhou_shop",
        ]));
        set("coor/x", -6265);
        set("coor/y", 2915);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}