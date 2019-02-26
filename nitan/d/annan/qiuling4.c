#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","丘陵");
  set ("long", @LONG
這裏是安南城南的一片丘陵地，丘陵起伏不平，紅褐色的巖石奇型
怪狀，沙石路到這裏逐漸隱沒於丘陵之中，因為這附近有強人出沒，行
人幾乎都不到這裏來。
LONG);

  set("exits", ([ 

  "south":__DIR__"qiuling3",
  "northeast":__DIR__"xiaolu2",
       ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
