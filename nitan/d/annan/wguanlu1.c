#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","官路");
  set ("long", @LONG
這裏是條官路。東邊是安南的西門。這裏的行人來來往往，有些熱
鬧。有很多車馬朝東邊走去，一派熱鬧的景象。不時有大隊的官兵
從你的身旁走過，嚇得路上的百姓都朝兩邊閃去。
LONG);

  set("exits", ([ 

  "east":__DIR__"ximen",
  "southwest":__DIR__"shalu1",
       ]));

set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
