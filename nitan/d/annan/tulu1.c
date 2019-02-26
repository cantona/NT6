#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","沙石路");
  set ("long", @LONG
這裏是安南城南的一條小路，因為不是主要的驛道，道路的狀況非
常不好，只是由沙石鋪成，路面顛簸不平，一陣風吹過，捲起漫天的沙
土。
LONG);

  set("exits", ([ 

  "north":__DIR__"nanmen",
  "south":__DIR__"tulu2",
       ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
