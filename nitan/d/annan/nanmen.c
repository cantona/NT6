#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",GRN"安南南門"NOR);
  set ("long", @LONG
這裏是安南的南門。這裏的行人不少。這裏有幾個官兵正在檢查來
往的百姓。旁邊有一個軍官耀武揚威地站在那裏，不停地指手畫腳。
LONG);

  set("exits", ([ 

  "north":__DIR__"suishilu2",
  "south":__DIR__"tulu1",
       ]));
  set("objects",([
          __DIR__"npc/bing":2,
          ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
