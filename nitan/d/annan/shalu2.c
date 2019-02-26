#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","沙石路");
  set ("long", @LONG
這裏是條沙石路。這裏的行人很少。據説這裏經常有強人出沒，你
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
