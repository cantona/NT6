#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",GRN"安南東門"NOR);
  set ("long", @LONG
這裡是安南的東門。這裡的行人不少。這裡有幾個官兵正在檢查來
往的百姓。旁邊還有幾個官兵在勒索想進城的百姓，有一個官兵還在旁
邊指手畫腳，一副神氣的樣子。
LONG);

  set("exits", ([ 

  "west":__DIR__"dongjie2",
  "east":__DIR__"xiaolu1",
       ]));
  set("objects",([
          __DIR__"npc/bing":2,
          ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
