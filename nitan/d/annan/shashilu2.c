#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","沙石路");
  set ("long", @LONG
這裡是條沙石路。這裡地勢一片空闊，四處望去一片平坦。不時有
鳥兒從你的頭上飛過。這裡沒有什麼人，你不禁加快了行進的腳步。
LONG);

  set("exits", ([ 

  "northwest":__DIR__"shashilu1",
  "southwest":__DIR__"qiuling6",
 // "west":__DIR__"hg",
       ]));
 
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
