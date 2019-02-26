#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","小路");
  set ("long", @LONG
你正走在一條崎嶇不平的山路上，偶爾聽到一陣陣的野獸叫聲，頭
頂有一些不知名的小鳥在跳來跳去，四周叢林密佈，鮮花綠草若隱若現，
隨着山谷裏吹來的陣陣清風，傳來嘩嘩的松濤聲和一些淡淡的花香。西
邊是安南的東門。這裏的行人很多。
LONG);

  set("exits", ([ 

  "west":__DIR__"xiaolu1",
  "southeast":__DIR__"shashilu1",
  "southwest":__DIR__"qiuling4",
       ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
