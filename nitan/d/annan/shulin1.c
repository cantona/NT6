#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","熱帶雨林");
  set ("long", @LONG
這裏是一片一望無垠林海，每棵樹木都有十來丈高，周圍阡陌交錯，
幾十丈高的大樹簇在一塊，密實的枝葉象一蓬蓬巨傘般伸向天空，把陽
光遮得絲毫也無。遠處似乎有幾個人在休息。
LONG);

  set("exits", ([ 
  "north":__DIR__"shulin1",
  "south":__DIR__"shulin9",
  //"east":__DIR__"shalu2",
  "southwest":__DIR__"shulin2",
  "west":__DIR__"xiaoxi",
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