#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","沙石路");
  set ("long", @LONG
這裏是安南城南的一條小路，因為不是主要的驛道，道路的狀況非
常不好，只是由沙石鋪成，路面顛簸不平，一陣風吹過，捲起漫天的沙
土。西邊的密林中隱約的有一條小路.
LONG);

  set("exits", ([ 

  "north":__DIR__"tulu1",
  "southeast":__DIR__"tulu3",
//  "southwest":__DIR__"shulin3",  
       ]));

set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
