#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","熱帶雨林");
  set ("long", @LONG
這裏是一片一望無垠林海，每棵樹木都有十來丈高，周圍阡陌交錯，
幾十丈高的大樹簇在一塊，密實的枝葉象一蓬蓬巨傘般伸向天空，把陽
光遮得絲毫也無。你側耳傾聽，似乎有溪水流動的聲音。
LONG);

  set("exits", ([ 
  "north":__DIR__"shulin1",
  "south":__DIR__"shulin2",

  "northeast":__DIR__"shulin1",
  "west":__DIR__"lu1",
  "southeast":__DIR__"shulin9",
    ]));

 set("objects",([
         __DIR__"npc/dushe":2,        
         ]));  
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
