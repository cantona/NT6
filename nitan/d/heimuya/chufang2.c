//chufang1.c
inherit ROOM;
void create()
{
  set("short","廚房");
        set("long", @LONG
這是白虎堂的廚房，一位美麗侍女滿臉堆笑。整個房間菜香胭脂
香迷漫。牆上貼着一張醒目的啟事(note)。
LONG );
  set("exits",([
      "west" : __DIR__"chitang",
  ]));
  set("item_desc",([
      "note" : "最難消受女人福，紅顏禍水。----->嶽不羣題\n",
  ]));

  set("objects",([
      __DIR__"npc/shinu" : 1,
      __DIR__"obj/tea" : random(6),
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
        ("侍女美目一挑，想走，沒門！\n");
        return ::valid_leave(me, dir);
}
