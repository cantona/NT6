#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","西街");
  set ("long", @LONG
這裏是安南的西街。西邊就是安南的西門了，有幾個官兵正在那裏
盤查着過往的行人。南邊有一家客棧，門口掛着的大紅燈籠遠遠就看得
清清楚楚。店小二正在門口熱情地招呼着客人。
LONG);

  set("exits", ([ 

  "west":__DIR__"ximen",
  "east":__DIR__"xijie1",
  "south":__DIR__"kezhan",
  "north":__DIR__"yanju",
       ]));
 set("objects",([
 __DIR__"npc/jiyinong":1,
 __DIR__"npc/bing":5,         
 ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
