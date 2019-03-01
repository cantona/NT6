#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","熱帶雨林");
  set ("long", @LONG
這裡是一片一望無垠林海，每棵樹木都有十來丈高，周圍阡陌交錯，
幾十丈高的大樹簇在一塊，密實的枝葉象一蓬蓬巨傘般伸向天空，把陽
光遮得絲毫也無。你側耳傾聽，似乎有溪水流動的聲音。
LONG);

  set("exits", ([ 
  "west":__DIR__"shulin6",
  "south":__DIR__"shulin4",

  "north":__DIR__"shulin6",
  "southwest":__DIR__"shulin8",
  "east":__DIR__"shulin4",
    ]));
   set("objects",([
         __DIR__"npc/daxiang":1,
         ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}

void init()
{
        add_action("do_go","go");;
}
int do_go()
{
if(random(3)){
this_player()->move(this_object());
return 1;
}
}