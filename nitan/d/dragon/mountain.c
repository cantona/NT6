inherit ROOM;
#include <ansi.h> 

void create ()
{
  set ("short", "瀑布");
  set ("long",HIG @LONG
蒼山峻嶺，峰勢崔巍，只見頂上白雲飄飄，崖前樹影寒寒，林
內鬆柏千千，四處怪石嶙嶙，令人舉步維難。瀑布聲震耳欲聾，水
花飛濺，如碎玉般漫天飄洒。山崖頂上隱隱有瑞氣祥雲，不知將有
何異象出現。
LONG);

  set("exits", ([
        "north"    : __DIR__"spirit9",
      ]));
  set("no_magic", 1);
        setup();
}

void init ()
{
  add_action ("do_climb","climb");
}

int do_climb (string arg)
{
  object who = this_player();

  message_vision ("$N手腳並用奮不顧身地向上爬去。\n",who);
  if( query("combat_exp", who)<10000 || 
      random(4))
  {
    message_vision ("\n……嘩嘩一聲，$N失手滑了下來。\n",who);
    who->unconcious();    
  }
  else
    who->move(__DIR__"yashang");
  return 1;
}
