#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","沙石路");
  set ("long", @LONG
這裏是條沙石路。一陣風吹過，捲起漫天的沙土。不時有人騎馬從
你身旁馳過。
LONG);

  set("exits", ([ 

  "northeast":__DIR__"wguanlu1",
  "southwest":__DIR__"shalu2",
       ]));

set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
