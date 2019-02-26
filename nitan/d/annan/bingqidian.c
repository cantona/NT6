#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","兵器店");
  set ("long", @LONG
這裏是家兵器店。由於現在處於戰亂時期，所以這裏生意很好。只
見鐵匠正在敲敲打打。旁邊地上的角落裏堆滿了各種兵器和護甲。只聽
乒乓聲中，又一件兵器打造好了。
LONG);

  set("exits", ([ 

  "west":__DIR__"suishilu2",
     ]));
 
  set("objects",([
          __DIR__"npc/tiejiang":1,
          ]));  
  
  set("valid_startroom", 1);
  setup();
 
}
