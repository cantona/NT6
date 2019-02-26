#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",GRN"安南北門"NOR);
  set ("long", @LONG
這裏是安南的北門。這裏的行人不少。這裏有幾個官兵正在檢查來
往的百姓。有個軍官耀武揚威地站在這裏，不停地指手畫腳。
LONG);

  set("exits", ([ 

  "south":__DIR__"qingshilu2",
  "north":__DIR__"guandao1",
       ]));
  set("objects",([
          __DIR__"npc/bing":2,
          ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
