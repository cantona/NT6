//chufang1.c
inherit ROOM;
void create()
{
  set("short","廚房");
        set("long", @LONG
你走在一條陰暗的林間小道上，兩旁是陰森森的樹林。一陣這是
風雷堂的廚房，一位美麗侍女滿臉堆笑。整個房間菜香胭脂香迷漫。
牆上貼着一張醒目的啟事(note)。
LONG );
  set("exits",([
      "east" : __DIR__"grass2",
  ]));
  set("item_desc",([
      "note" : "人是鐵，飯是鋼，一頓不吃餓得慌。\n",
  ]));

  set("objects",([
      __DIR__"npc/shinu" : 1,
    __DIR__"obj/tea" : 1 + random(5),
      __DIR__"obj/sherou"  : random(4),
  ]));
//  set("no_clean_up", 0);
  setup();
}
int valid_leave(object me, string dir)
{
        if (( present("tea", me)||present("she rou", me))
        &&objectp(present("shi nu", environment(me))) )
        return notify_fail
        ("侍女美目一挑，你還是在這兒吃完吧。\n");
        return ::valid_leave(me, dir);
}
