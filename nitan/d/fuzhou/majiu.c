// Room: /d/fuzhou/majiu.c
// Date: May,31 1998 Java

inherit ROOM;

void create()
{
        set("short","馬廄");
        set("long",@LONG
這是榕城驛的馬廄，常年供應新鮮草料。福州民風淳樸，馬伕們會
把馬牽到馬廄好生照看，將它們餵飽飲足，再洗刷得幹乾淨淨，一直伺
候到客人上路。馬廄雨檐下的爛木柱上釘着一塊破木牌(paizi)。
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
          泉州城:  rideqz

TEXT]));
        set("exits",([ /* sizeof() == 1 */
                "south" : __DIR__"rongcheng",
                "up"    : SHOP_DIR"fuzhou_shop",
        ]));
	set("coor/x", -70);
	set("coor/y", -6160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}