#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","沙石路");
  set ("long", @LONG
這裡是條沙石路。這裡的行人很少。據說這裡經常有強人出沒，你
不禁小心起來。
LONG);

  set("exits", ([ 

  "northeast":__DIR__"shalu1",
  //"west":__DIR__"shulin1",
       ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
