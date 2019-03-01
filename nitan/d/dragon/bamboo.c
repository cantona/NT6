#include <room.h>
inherit ROOM;

void create()
{
      set("short","紫竹林");
      set("long",
"錦繡花園後的紫竹林，是夜辰閒時休憩常到的所在。紫竹細疏，清風\n"
"微拂。漫步于此，世事之紛擾頓時煙消雲散。\n"
);
      set("exits",([ /* sizeof() == 1 */
          "west"  : __DIR__"bamboo2",
          "north"  : __DIR__"bamboo1",
      ]));
      set("no_magic", 1);
        setup();
}
