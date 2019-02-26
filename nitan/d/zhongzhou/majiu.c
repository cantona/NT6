#include <room.h>
inherit TRANS_ROOM;

void create()
{
mapping map_short = ([
         "nanyang"       : "南陽",
         "suzhou"        : "蘇州",
         "luoyang"       : "洛陽",
         "beijing"       : "北京",
         "xiangyang"     : "襄陽",
         "kaifeng"       : "開封",
         "changan"       : "長安",
         "yangzhou"      : "揚州",
]);

mapping trans_pay = ([
         "nanyang"       : 120,
         "suzhou"        : 80,
         "luoyang"       : 120,
         "beijing"       : 150,
         "xiangyang"     : 80,
         "kaifeng"       : 100,
         "changan"       : 100,
         "yangzhou"      : 80,
]);

      set("short", "馬廄");
      set("long", @LONG
這裏是中州城英豪酒樓後的馬廄，常年供應新鮮草料。中
州城自古乃軍事要地，民風淳樸，馬伕們會把馬牽到馬廄好生
照看，將它們餵飽飲足，再洗刷得幹乾淨淨，一直伺候到客人
上路。馬廄雨檐下的爛木柱上釘着一塊破木牌 (paizi)。馬廄
中堆放著幾堆草料，正中有一口泔槽。
LONG);
      set("outdoors", "zhongzhou");
      set("no_fight", 1);
      set("objects", ([
              "/clone/horse/zaohongma": 1,
              "/clone/horse/huangbiaoma": 1,
              "/clone/horse/ziliuma": 1,
              "/clone/npc/mafu": 1,
      ]));
      set("exits",([
              "west" : __DIR__"yinghao",
              "up"   : "/clone/shop/zhongzhou_shop",
      ]));
        set("trans", map_short);
        set("trans_money", trans_pay);
        set("coor/x", -9020);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
      replace_program(TRANS_ROOM);
}