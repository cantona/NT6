#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short", "馬廄");
        set("long", @LONG
這裡是揚州客店後的馬廄，常年供應新鮮草料。揚州民風淳樸，
馬夫們會把馬牽到馬廄好生照看，將它們喂飽飲足，再洗刷得幹乾凈
凈，一直伺候到客人上路。馬廄雨檐下的爛木柱上釘著一塊破木牌 (
paizi）。馬廄中堆放著幾堆草料。
LONG );
      set("outdoors", "city");
      set("no_fight", 1);
      set("objects", ([
              "/clone/horse/zaohongma": 1,
              "/clone/horse/huangbiaoma": 1,
              "/clone/horse/ziliuma": 1,
              "/clone/npc/mafu": 1,
      ]));
      set("exits",([
              "west" : __DIR__"kedian",
              "up"   : "/clone/shop/yangzhou_shop",
                "north" : __DIR__"business",
              "south" : __DIR__"hero_shop",
      ]));
	set("coor/x", 20);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
}
