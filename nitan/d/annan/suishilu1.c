inherit ROOM;


void create ()
{
  set ("short","碎石路");
  set ("long", @LONG
這裡是條碎石路。這裡的行人很少。四周也沒有什麼建築物，顯得
有些冷清。北邊不時傳來熱鬧的聲音。只見幾個安南幫弟子從你的身旁
走過，不時回頭打量了你幾眼。
LONG);

  set("exits", ([ 

  "north":__DIR__"xijie1",
  "south":__DIR__"suishilu2",
       ]));
 
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
