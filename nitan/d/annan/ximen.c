#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",GRN"安南西門"NOR);
  set ("long", @LONG
這裏是安南的西門。這裏的行人不少。這裏有幾個官兵正在檢查來
往的百姓。旁邊有個官兵耀武揚威地站在那裏，不停地在那裏指手畫腳。
LONG);

  set("exits", ([ 

  "east":__DIR__"xijie2",
  "west":__DIR__"wguanlu1",
       ]));
  set("objects",([
          __DIR__"npc/bing":2,
          ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
