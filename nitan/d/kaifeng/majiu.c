#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short", "馬廄");
        set("long", @LONG
這是稻香居後的馬廄，常年供應新鮮草料。開封府自古乃軍事重
地，歷史悠久，民風淳樸。馬夫們會把馬牽到馬廄好生照看，將它們
喂飽飲足，再洗刷得幹乾凈凈，一直伺候到客人上路。馬廄雨檐下的
爛木柱上釘著一塊破木牌 (paizi)。馬廄中堆放著幾堆草料，正中有
一口泔槽。
LONG );
        set("outdoors", "kaifeng");
        set("no_fight", 1);
        set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
        ]));
        set("exits",([
               "west" : __DIR__"daoxiang",
               "north" : __DIR__"business",
               "up"   : "/clone/shop/kaifeng_shop",
        ]));
	set("coor/x", -5030);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}