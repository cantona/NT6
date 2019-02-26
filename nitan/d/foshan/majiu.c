#include <room.h>
inherit TRANS_ROOM;

void create()
{
        set("short","馬廄");
        set("long", @LONG
這裏是佛山鎮的馬廄，常年供應新鮮草料。佛山民風淳樸馬伕們
會把馬牽到馬廄好生照看，將它們餵飽飲足，再洗刷得幹乾淨淨，一
直伺候到客人上路。馬廄雨檐下的爛木柱上釘着一塊破木牌(paizi)。
馬廄中堆放著幾堆草料。
LONG );
      set("exits",([
                "north" : __DIR__"yingxionglou",
                "up"    : "/clone/shop/foshan_shop",
      ]));
      set("outdoors", "foshan");
      set("no_fight", 1);
      set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
      ]));
	set("coor/x", -6560);
	set("coor/y", -9770);
	set("coor/z", 0);
	setup();
      replace_program(TRANS_ROOM);
}