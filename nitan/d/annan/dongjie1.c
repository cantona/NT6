inherit ROOM;


void create ()
{
  set ("short","東街");
  set ("long", @LONG
這裏是安南的東街，這裏的行人很多。西邊是安南的中心了，那裏
傳來了熱鬧的聲音。南邊是一條小巷，陰暗無光，是地痞流氓聚集的場
所，裏面傳來了吵架、打罵的聲音。
LONG);

  set("exits", ([ 

  "northwest":__DIR__"center",
  "east":__DIR__"dongjie2",
  "south":__DIR__"xiaoxiang1",
       ]));
 
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
