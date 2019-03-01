//room: didao4.c
inherit ROOM;

void create()
{
  set("short","秘道盡頭");
        set("long", @LONG
你忽覺前方有一亮光，真是別有洞天，前方好像別有地方。
LONG );
  set("exits",([
      "east"   :__DIR__"didao1",
      "west"  :__DIR__"didao3",
      "south" : __DIR__"didao4",
      "southup" : __DIR__"didao6",
  ]));
  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}