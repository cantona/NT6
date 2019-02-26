#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","紅河道");
  set ("long", @LONG
這裏是條官路。南邊是安南的北門。這裏的行人來來往往，有些熱
鬧。南來北往的有很多車馬，一派熱鬧的景象。不時有飛馳快馬從你身
邊跑過，嚇得路上的百姓都朝兩邊閃去。
LONG);

  set("exits", ([ 

  "south":__DIR__"beimen",
  "north":__DIR__"guandao2",
       ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
