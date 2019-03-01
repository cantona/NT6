#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","西街");
  set ("long", @LONG
這裡是安滹的西街。北面有一家酒館，裡面傳來了陣陣的酒香。往
西走就可以到安南的西門了。只見幾個喝醉的豪客正從酒館中出來，搖
搖晃晃地朝西邊走去了。
LONG);

  set("exits", ([ 

  "northeast":__DIR__"center",
  "west":__DIR__"xijie2",
  "northwest":__DIR__"jiuguan",
  "south":__DIR__"suishilu1",
       ]));
 set("objects",([
         __DIR__"npc/xiaojie":1,
         ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
