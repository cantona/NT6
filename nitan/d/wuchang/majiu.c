//Edited by fandog, 02/15/2000
inherit ROOM;

void create()
{
      set("short","馬廄");
      set("long",@LONG
這是客店後的馬廄，常年供應新鮮草料。客人們在此歇息，馬伕會
把馬牽到馬廄好生照看，將它們餵飽飲足，再洗刷得乾乾淨淨，一直伺
候到客人上路。馬廄雨檐下的爛木柱上釘着一塊破木牌(paizi)。
    馬廄中堆放著幾堆草料，正中有一口泔槽。
LONG);
        set("outdoors", "wuchang");
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
                "north" : __DIR__"kedian",
                "up"   : SHOP_DIR"wuchang_shop",
        ]));
	set("coor/x", -5100);
	set("coor/y", -1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}