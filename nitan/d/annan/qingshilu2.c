inherit ROOM;


void create ()
{
  set ("short","青石路");
  set ("long", @LONG
這裏是條青石路。北邊是安南的北門。這裏的行人很多，往南邊走
就可以到安南的中心了。由於近年安南幫活動猖獗，他們有是以販賣人
口為職業，所以安南的街頭少見年輕女子了。
LONG);

  set("exits", ([ 

  "south":__DIR__"qingshilu1",
// "east":"/d/clone/room/cityroom/baling",
  "north":__DIR__"beimen",
       ]));
 set("objects",([
         __DIR__"npc/boy":1,
         ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
