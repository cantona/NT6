#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","軍營");
  set ("long", @LONG
這裡是安南的駐軍大營。這裡幾乎都是官兵，一隊官兵正在那裡操
練，傍邊有一個軍官摸樣的在那裡指手畫腳，好象是官軍的頭子。
你在這裡十分的礙眼，你匆匆的走來
LONG);

  set("exits", ([ 

  "south":__DIR__"yingmen",
       ]));
set("objects",([
          __DIR__"npc/bing":5,
          __DIR__"npc/daxiang":2,
          ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
