#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short","馬廄");
        set("long", @LONG
這是草棚邊的馬廄，常年供應新鮮草料。馬伕們會把馬牽到馬廄
好生照看，將它們餵飽飲足，再洗刷得幹乾淨淨，一直伺候到客人上
路。馬廄中堆放著幾堆草料正中有一口泔槽。馬廄雨檐下的爛木柱上
釘着一塊破木牌(paizi)。
LONG );
      set("outdoors", "emei");
      set("exits",([
              "east"    : __DIR__"caopeng",
      ]));
      set("no_fight", 1);
      set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
      ]));
        set("coor/x", -390);
        set("coor/y", -200);
        set("coor/z", 0);
        setup();
      replace_program(TRANS_ROOM);
}