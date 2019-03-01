inherit ROOM;

void create()
{
        set("short", "十二蓮台");
        set("long", @LONG
這裡是武當絕頂的十二蓮台，台與台之間以曲欄相連，雕刻精美，
是遠眺的最佳所在。站立此台四眺，宛如身在千葉寶蓮之上，千峰萬
壑都在腳下。往西可望到七百裡外的華山，東望則漢水如練，襄、樊
一帶盡收眼底。
LONG );
        set("exits", ([
                "east" : __DIR__"jinding",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("honglian",1);
        set("coor/x", -360);
        set("coor/y", -420);
        set("coor/z", 180);
        setup();
}
void init()
{
      add_action("do_find","find");
}

int do_find()
{
      object obj;
      object me = this_player();

      if( query("jingli", me)<50 )
            return notify_fail("你找得兩眼酸痛，都沒有發現什麼好東西。\n");

      addn("jingli", -10, me);

      if (!query("honglian"))
            return notify_fail("你找了半天，什麼都沒有找到。\n");

      addn("honglian",-1);
      obj = new("/d/wudang/obj/honglian");
      obj->move(me);
      tell_object(me,"你找了半天，突然發現一顆紅色小草，開著一朵極象蓮座的小花。\n");
      return 1;
}

void reset()
{
      ::reset();
      set("honglian",1);
}