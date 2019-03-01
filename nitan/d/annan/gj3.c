#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","吳哥窟");
  set ("long", @LONG
十二世紀中期為供奉印度教毗濕奴神所建，可能是世界上最大
寺廟。13世紀後期，變成佛教寺廟。它由東南西北四廊（每廊又分
兩翼），西參道、正門、三重回廊及以主殿中央尖塔為中心的五座
尖塔所構成。除西門外，另三面是假門，佛法認為人死後登西方極
樂，因此敞開西門讓靈魂得以升天。吳哥窟是現存吳哥遺跡中規模
最大、保護得最好的代表之作。
LONG);

  set("exits", ([ 
"east":__DIR__"matou",        

       ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
