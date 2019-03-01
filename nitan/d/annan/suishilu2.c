#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","碎石路");
  set ("long", @LONG
這裡是條碎石路。南邊就是安南的南門了。東邊有一家兵器店，那
裡傳來敲敲打打的聲音。那家兵器店以制作護具出名，很多武林人士都
到那裡去買盔甲、盾牌等。
LONG);

  set("exits", ([ 

  "north":__DIR__"suishilu1",
  "south":__DIR__"nanmen",
  "east":__DIR__"bingqidian",
   "west":__DIR__"hg",
       ]));
 
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
