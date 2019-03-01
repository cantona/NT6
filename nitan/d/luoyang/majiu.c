#include <room.h>
inherit TRANS_ROOM;

void create()
{
mapping map_short = ([
         "nanyang"     : "南陽",
         "wugong"      : "武功鎮",
         "yangzhou"    : "揚州",
         "kaifeng"     : "開封",
         "changan"     : "長安",
         "beijing"     : "北京",
         "zhongzhou"   : "中州",
         "xiangyang"   : "襄陽",
]);

mapping trans_pay = ([
         "nanyang"     : 120,
         "wugong"      : 80,
         "yangzhou"    : 160,
         "kaifeng"     : 140,
         "changan"     : 100,
         "beijing"     : 160,
         "zhongzhou"   : 120,
         "xiangyang"   : 100,
]);

        set("short","馬廄");
        set("long",@LONG
這是客店後的馬廄，常年供應新鮮草料。洛陽乃天下古城
歷史悠久、民風淳樸，馬夫們會把馬牽到馬廄好生照看，將它
們喂飽飲足，再洗刷得幹乾凈凈。馬廄雨檐下的爛木柱上釘著
塊破木牌 (paizi)。馬廄中堆放著幾堆草料。
LONG);
        set("outdoors", "luoyang");
        set("no_fight", 1);
        set("objects", ([
              "/clone/horse/zaohongma": 1,
              "/clone/horse/huangbiaoma": 1,
              "/clone/horse/ziliuma": 1,
              "/clone/npc/mafu": 1,
        ]));
        set("exits",([
                "west" : __DIR__"kezhan",
                "up"   : "/clone/shop/luoyang_shop",
        ]));
        set("trans", map_short);
        set("trans_money", trans_pay);

	set("coor/x", -6970);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}