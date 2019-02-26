#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","沙石路");
  set ("long", @LONG
這裏是條沙石路，一陣風吹過，捲起漫天黃沙。這裏地勢一片空闊，
四處望去一片平坦。不時有鳥兒從你的頭上飛過。
LONG);

  set("exits", ([ 

  "northwest":__DIR__"xiaolu2",
  "southeast":__DIR__"shashilu2",
       ]));
 
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
