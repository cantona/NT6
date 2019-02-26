inherit ROOM;
#include <ansi.h> 
void create ()
{
  set ("short", "迷霧");
  set ("long", HIG@LONG
這裏一片朦朧，什麼都看不清。但在迷霧中彷彿包藏着無盡的
殺機。忽然間三隻奇怪的野獸從朦朧中猛撲出來，爪如鋼刀，須如
利劍，你措手不及，頓時陷入了包圍中。
LONG);

  set("exits", ([
         "west"    : __DIR__"outlet1",
         "south"    : __DIR__"entrance",
      ]));
  set("objects", ([
         "/quest/tulong/npc/beast" : 3,
      ]));
  set("no_magic", 1);
        setup();
}

int valid_leave (object me, string dir)
{
  object beast = present("beast", this_object());

  if (dir == "west" &&  beast &&
      ! beast->is_busy() )
    return notify_fail("觀想獸擋住去路，死活不讓你過！\n");
  return ::valid_leave(me,dir);
}
