#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","小溪");
  set ("long", @LONG
這裡是條小溪。溪水清澈見底，還有幾條魚在遊來遊去。這裡風景
秀麗，山水如畫，空氣清新。地上有很多漂亮的野花、蒲公英等植物。
不時有野兔從你的腳旁跳過。
LONG);

  set("exits", ([ 

  "east":__DIR__"shulin1",
    ]));
  set("objects",([
          __DIR__"npc/she":2,
          ]));
  set("resource/water",1);
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
