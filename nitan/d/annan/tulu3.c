#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","沙石路");
  set ("long", @LONG
這裡是安南城南的一條小路，因為不是主要的驛道，道路的狀況非
常不好，只是由沙石舖成，路面顛簸不平，一陣風吹過，卷起漫天的沙
土。
LONG);

  set("exits", ([ 

  "northwest":__DIR__"tulu2",
  "northeast":__DIR__"qiuling1",  
       ]));

set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
