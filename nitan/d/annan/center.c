#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","安南中央廣場");
  set ("long", @LONG
漫步安南，新老建築交相輝映，安南人不分老幼都有愛嚼檳榔的
習慣嘴裏總是紅紅的，安南少女愛穿紅色的筒裙，而那些戴着大斗笠
的婦女大都是郊區婦女，她們出門必戴斗笠，既能遮陽又能擋雨。 
LONG);

  set("exits", ([ 
"west":__DIR__"gj1",
"east":__DIR__"gj2",        
  "southwest":__DIR__"xijie1",
  "southeast":__DIR__"dongjie1",
  "north":__DIR__"qingshilu1",
       ]));
 set("objects",([
         __DIR__"npc/bing2":1,
         __DIR__"npc/bldizi":1,
         ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
