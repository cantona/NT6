#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","紅河道");
  set ("long", @LONG
這裡是條官路。因著名的紅河因土質呈土紅色得名。這裡的行人來來
往往，有些熱鬧。南來北往的有很多車馬，一派熱鬧的景象。不時有
飛馳快馬從你身邊跑過，嚇得路上的百姓都朝兩邊閃去。
LONG);

  set("exits", ([ 

  "south":__DIR__"guandao2",
  "north":__DIR__"guandao4",
  "northwest":__DIR__"yingmen",
       ]));

set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
