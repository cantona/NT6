#include <ansi.h>
inherit ROOM;

void create ()
{
  set ("short","小巷");
  set ("long", @LONG
這裡是條小巷。平時有很多地痞流氓聚集在這裡。只見這裡人聲嘈
雜，賭博叫罵的聲音不絕于耳。
LONG);

  set("exits", ([ 

  "north":__DIR__"dongjie1",
     ]));
 set("objects",([
         __DIR__"npc/liumang":1,
        __DIR__"npc/liumang2":1,
         ]));
set("outdoors","annan");
  set("valid_startroom", 1);
  setup();
 
}
