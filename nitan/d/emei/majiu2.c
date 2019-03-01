#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short","馬廄");
        set("long", @LONG
這是草棚邊的馬廄，常年供應新鮮草料。馬夫們會把馬牽到馬廄
好生照看，將它們喂飽飲足，再洗刷得幹乾凈凈，一直伺候到客人上
路。馬廄中堆放著幾堆草料，正中有口泔槽。馬廄雨檐下的爛木柱上
釘著一塊破木牌(paizi)。
LONG );
      set("outdoors", "emei");
      set("exits",([
                "south" : __DIR__"huayanding",
      ]));
      set("no_fight", 1);
      set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
      ]));
        set("coor/x", -520);
        set("coor/y", -230);
        set("coor/z", 120);
        setup();
      replace_program(TRANS_ROOM);
}