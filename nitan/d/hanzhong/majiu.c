#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short","馬廄");
        set("long", @LONG
這是武功鎮的馬廄，因為平時來往的人不多，顯得有些破舊。馬
廄雨檐下的爛木柱上釘著一塊破木牌 (paizi)。廄中堆放著幾堆草料，
正中有一口泔槽。
LONG );
      set("outdoors", "hanzhong");
      set("no_fight", 1);
      set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
      ]));
      set("exits",([ /* sizeof() == 1 */
                "west" : __DIR__"kedian1",
      ]));
        set("coor/x", -12230);
	set("coor/y", 820);
	set("coor/z", 0);
	setup();
      replace_program(TRANS_ROOM);
}
