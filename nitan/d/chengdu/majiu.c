#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short", "馬廄");
        set("long", @LONG
這是成都城的馬廄，常年供應新鮮草料。成都民風淳樸馬伕們會
把馬牽到馬廄好生照看，將它們餵飽飲足，再洗刷得幹乾淨淨，一直
伺候到客人上路。馬廄雨檐下的爛木柱上釘着塊破木牌(paizi)。馬廄
中堆放著幾堆草料。
LONG );
      set("outdoors", "chengdu");
      set("no_fight", 1);
      set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
      ]));
      set("exits", ([
                "west" : __DIR__"kedian",
                "up"   : "/clone/shop/chengdu_shop",
      ]));
        set("coor/x", -15190);
	set("coor/y", -1860);
	set("coor/z", 0);
	setup();
      replace_program(TRANS_ROOM);
}