#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","軍營大門");
  set ("long", @LONG
這裡是安南的駐軍大營。這裡幾乎沒有行人進進出出的多是官兵，
不時也有武林人物進出，門口有兩個士兵在站崗，好象一般的人是
不讓進出的。安南軍中還有很多大象。
LONG);

  set("exits", ([ 

  "southeast":__DIR__"guandao3",
  "north":__DIR__"yingdi",
       ]));
set("objects",([
          __DIR__"npc/bing":5,
          __DIR__"npc/daxiang":2,        
          ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
