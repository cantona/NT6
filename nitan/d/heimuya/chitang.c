//room: 
inherit ROOM;

void create()
{
  set("short","池塘");
        set("long", @LONG
這是一個小池塘，池塘裏有數對鴛鴦悠遊其間，池邊還有四隻白
鶴在覓食。
LONG );

  set("exits",([
      "north" : __DIR__"baihutang",
//      "west"  : __DIR__"shenggu",
      "east"  :__DIR__"chufang2",
  ]));
  set("objects",([
      "/d/dali/npc/xianhe" : 4,
  ]));
//  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}
