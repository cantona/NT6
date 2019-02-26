#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","西湖");
  set ("long", @LONG
安南西湖，面積500公頃，是河內第一大著名風景區，古蹟在這裏也比較
集中，鎮國寺、鎮武觀、金蓮寺等，與國內古寺相仿。位於河內還劍湖西的
文廟，是古代王朝祀奉孔子的地方，文廟坐北朝南，紅牆綠瓦，是一座典雅
的中國風格的建築羣。可以看出它與中國傳統文化有着甚深的淵源。 
LONG);

  set("exits", ([ 
"east":__DIR__"center",        

       ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
