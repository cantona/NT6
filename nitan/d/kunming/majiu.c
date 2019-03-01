#include <room.h>
inherit TRANS_ROOM;

void create()
{
mapping map_short = ([
         "chengdu"     : "成都",
         "dali"        : "大理",
         "jingzhou"    : "荊州",
         "emei"        : "峨嵋山",
         "xiangyang"   : "襄陽",
]);

mapping trans_pay = ([
         "chengdu"     : 120,
         "dali"        : 150,
         "jingzhou"    : 140,
         "emei"        : 120,
         "xiangyang"   : 500,
]);

              set("short","馬廄");
              set("long",@LONG
這是元人客棧後的馬廄，常年供應新鮮草料。昆明民風淳
樸，馬夫們會把馬牽到馬廄好生照看，將它們喂飽飲足，再洗
刷得幹乾凈凈，一直伺候到客人上路。馬廄雨檐下的爛木柱上
釘著一塊破木牌 (paizi)。馬廄中堆放著幾堆草料，正中有一
口泔槽。
LONG);
        set("outdoors", "kunming");
        set("no_fight", 1);
        set("objects", ([
                      "/clone/horse/zaohongma": 1,
                      "/clone/horse/huangbiaoma": 1,
                      "/clone/horse/ziliuma": 1,
                      "/clone/npc/mafu": 1,
              ]));
              set("exits",([
                      "east"      : __DIR__"kedian",
              ]));
        set("trans", map_short);
        set("trans_money", trans_pay);

	set("coor/x", -16860);
	set("coor/y", -7230);
	set("coor/z", 0);
	setup();
              replace_program(TRANS_ROOM);
}