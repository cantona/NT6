#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","紅河");
  set ("long", @LONG
紅河發源於中國雲南省巍山縣，在中國境內稱為元江，全長1200公里，
在中國雲南境內長695公里在安南境內長505公里,紅河和湄公河水力
資源豐富。海岸線長3260千米，沿岸多天然良港。
LONG);

  set("exits", ([ 
  "north":__DIR__"shulin1",
  "south":__DIR__"matou",

  //"northeast":__DIR__"tulu2",
  "northwest":__DIR__"shulin4",
    ]));
   set("objects",([
         __DIR__"npc/daxiang":1,
         ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
