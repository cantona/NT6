//room: didao5.c
inherit ROOM;

void create()
{
  set("short","秘道");
        set("long", @LONG
走在裡面，你不覺想到這似乎在每個角落都藏著無限殺機，你感
到近了近了，越來越近了。
LONG );

  set("exits",([
      "east" : __DIR__"didao3",
      "west" : __DIR__"didao3",
      "north" : __DIR__"didao2",
      "south" : __DIR__"didao1",
  ]));
  set("objects",([
      "/clone/beast/dushe" : 4,
  ]));
  setup();
  replace_program(ROOM);
}