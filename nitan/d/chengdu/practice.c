// Room: practice
// Date: Feb.14 1998 by Java

#include <room.h>
inherit ROOM;

void create()
{
      set("short", "武館操練房");
        set("long", @LONG
這裏擺滿了石鎖簸箕、大刀長劍、沙袋綁腿等，還有幾個精心制
造的木人，是武館弟子日常練功的地方。
LONG );

      set("exits", ([ /* sizeof() == 1 */
          "down"   : __DIR__"wuguan",
      ]));

      set("objects", ([
          "/clone/npc/mu-ren" : 4,
      ]));

        set("coor/x", -15200);
	set("coor/y", -1800);
	set("coor/z", 10);
	setup();
      replace_program(ROOM);
}