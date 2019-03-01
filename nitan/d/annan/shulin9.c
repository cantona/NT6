#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","湄公河");
  set ("long", @LONG
湄公河發源于中國青藏高原，上遊稱瀾滄江，經老撾、泰國、柬埔寨
流入安南南部，分為南北幹流，北幹流稱前江，南幹流稱後江，最後
兩條幹流又分成九條支流入海，故又稱九龍江。
LONG);

  set("exits", ([ 
  "south":__DIR__"shulin7",
  "northwest":"/d/lumaji/s_kou",

  "west":__DIR__"shulin2",
  "northeast":__DIR__"shulin7",
  "southeast":__DIR__"shulin8",
    ]));
   set("objects",([
         __DIR__"npc/daxiang":1,
         __DIR__"npc/tiger":1,        
         __DIR__"npc/dushe":2,        
         ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
