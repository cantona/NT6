inherit ROOM;
#include <ansi.h> 

void create ()
{
  set ("short", "青木林出口");
  set ("long", HIG @LONG
突然無數棵參天大樹中出現了一條小徑，似乎是出口！□LONG);

  set("exits", ([
      ]));

  set("no_magic", 1);
        setup();
}

int valid_leave (object me, string dir)
{
  set("startroom", "/d/city/wumiao", me);
  set_temp("lost_in_greenyard", 0, me);
  set_temp("out_of_greenyard", 0, me);
  return 1;
}
