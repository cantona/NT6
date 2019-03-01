//Room: majiu.c 馬廄
//Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
        set("short","馬廄");
        set("long",@LONG
這是客棧邊上的馬廄，常年供應新鮮草料。據說此地民風淳樸，客
人只要住店，馬夫們就會把馬牽到馬廄好生照看，將它們喂飽飲足，再
洗刷得幹乾凈凈。一直伺候到客人離店上路。馬廄中堆放著幾堆草料，
正中有一口泔槽。馬廄雨檐下的爛木柱上釘著一塊破木牌(paizi)。
LONG);
        set("outdoors", "yongdeng");
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
          靈州城:  ridelz

TEXT]));
        set("exits",([ /* sizeof() == 1 */
            "east"      : __DIR__"kedian",
        ]));
        set("coor/x", -16130);
	set("coor/y", 4200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}