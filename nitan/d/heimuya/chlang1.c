//room: 
inherit ROOM;

void create()
{
  set("short","長廊");
        set("long", @LONG
這裡是非常氣派的長廊。兩邊站著數十個刀斧手，警衛森嚴，透
著騰騰殺氣。
LONG );

  set("exits",([
      "north" : __DIR__"dating3",
      "south" : __DIR__"chlang2",
  ]));
  set("objects",([
     __DIR__"npc/jiaotu"   :1,
  ]));
//  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}
