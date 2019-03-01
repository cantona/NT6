inherit ROOM;


void create ()
{
  set ("short","東街");
  set ("long", @LONG
這裡是安南的東街。東邊就是安南的東門了。北面有一家錢莊，錢
莊的金字招牌在陽光的照耀下閃閃發光。東邊的東門傳來了官兵吆喝的
聲音。
LONG);

  set("exits", ([ 

  "north":__DIR__"qianzhuang",
  "east":__DIR__"dongmen",
  "west":__DIR__"dongjie1",
      ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
