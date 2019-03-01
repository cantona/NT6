#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","安南酒館");
  set ("long", @LONG
這裡是一家酒館，看起來生意非常好，店小二跑來跑去，忙個不停
。幾個酒客正在那裡喝酒暢談。門口飄揚著一面大旗，上面寫著「安南
酒館」四個大字，迎風飄揚，似乎在招呼著南來北往的客人。
LONG);

  set("exits", ([ 

  "southeast":__DIR__"xijie1",
      ]));
 
  set("objects",([
          __DIR__"npc/xiaoer":1,
          ]));
  set("valid_startroom", 1);
  setup();
 
}
