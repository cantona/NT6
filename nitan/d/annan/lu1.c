#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","小路");
  set ("long", @LONG
你正走在一條崎嶇不平的山路上，偶爾聽到一陣陣的野獸叫聲，頭
頂有一些不知名的小鳥在跳來跳去，四周叢林密布，鮮花綠草若隱若現，
隨著山谷裡吹來的陣陣清風，傳來嘩嘩的鬆濤聲和一些淡淡的花香。
LONG);

  set("exits", ([ 

  "east":__DIR__"shulin2",
//  "southwest":"/d/xiangyang/shalu3",
    ]));
  
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
