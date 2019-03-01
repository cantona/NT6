inherit ROOM;


void create ()
{
  set ("short","青石路");
  set ("long", @LONG
這裡是條青石路。南邊就是安南的中心了，那邊傳來了熱鬧的聲音。
東邊有一家妓院，裡面傳來了陣陣笑聲。有幾個女子正在門口招呼著來
往的客人，當然有很多公子哥、江湖莽漢朝裡邊走去了。
LONG);

  set("exits", ([ 

  "south":__DIR__"center",
  "east":__DIR__"yingjunlou",
  "north":__DIR__"qingshilu2",
       ]));
 
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
