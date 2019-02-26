#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","迎君樓");
  set ("long", @LONG
這裏是安南最大的春樓--“迎君樓”。門口有幾個姑娘在招呼來往
的行人。抬頭望去，這座樓足有三層之高，每層樓上都傳來調笑的聲音。
「迎君樓」大招牌掛在最上面，似乎比王府貴族還要氣派。不時有安南
幫的弟子從這裏出出入入。
LONG);

  set("exits", ([ 

  "west":__DIR__"qingshilu1",
       ]));
 set("objects",([
         __DIR__"npc/xiaocui":1,
         ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
