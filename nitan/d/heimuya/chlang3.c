//chlang3
inherit ROOM;

void create()
{
  set("short","長廊");
        set("long", @LONG
這裏是非常氣派的長廊，戒備森嚴。東邊就是日月神教聖姑任大
小姐的居室。
LONG );
  set("exits",([
      "east"  : __DIR__"shenggu",
      "west"  : __DIR__"dating4",
      "south" : __DIR__"restroom2",
  ]));                     
  set("no_fight",0);
  set("no_steal",0);
  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}
