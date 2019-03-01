//restroom2.c
inherit ROOM;

void create()
{
  set("short","休息室");
        set("long", @LONG
這裡是間休息室，裡面有張大床。在這裡睡覺非常舒服，沒人能
打擾。往北是一條長廊。
LONG );
  set("exits",([
      "north" : __DIR__"chlang3",
  ]));
  set("sleep_room", 1);
  set("no_fight",1);
  set("no_steal",1);
  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}
