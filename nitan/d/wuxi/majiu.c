//Room: majiu.c 馬廄
// Winder 2000.3.10

inherit ROOM;

void create()
{
        set("short","馬廄");
        set("long",@LONG
這是客店邊的馬廄，常年供應新鮮草料。據說此地民風淳樸，馬夫
們會把馬牽到馬廄好生照看，將它們喂飽飲足，再洗刷得幹乾凈凈，一
直伺候到客人上路。馬廄中堆放著幾堆草料，正中有一口泔槽。
    馬廄雨檐下的爛木柱上釘著一塊破木牌(paizi)。
LONG);
        set("outdoors", "wuxi");
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
客人們只要給馬夫一兩白銀的租金就可以雇到一匹馬了。

前往      揚州城:   rideyz

TEXT]));
        set("exits",([ /* sizeof() == 1 */
                "south" : __DIR__"kedian",
                "up"    : SHOP_DIR"wuxi_shop",
        ]));
        set("coor/x", 1020);
	set("coor/y", -710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}