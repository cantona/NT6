#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","紅河道");
  set ("long", @LONG
這裏是條官路。因著名的紅河因土質呈土紅色得名。南邊是安南的北門。
這裏的行人來來往往，有些熱鬧。南來北往的有很多車馬，一派熱鬧
的景象。
LONG);

  set("exits", ([ 

  "south":__DIR__"guandao3",
  "north":__DIR__"matou",
       ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
