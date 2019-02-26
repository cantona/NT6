//room: didao6.c
inherit ROOM;

void create()
{
  set("short","祕道盡頭");
        set("long", @LONG
你忽覺前方一亮，身前真是別有洞天，前方好想有作花園。不知
是什麼地方。
LONG );
  set("exits",([
      "north"     : __DIR__"xiaohuayuan",
      "northdown" : __DIR__"didao4",
  ]));
  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}