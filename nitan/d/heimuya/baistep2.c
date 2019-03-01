//room: 
inherit ROOM;
void create()
{
  set("short","長廊");
        set("long", @LONG
這裡是白虎堂的長廊。兩邊一片狼籍，看樣子剛被洗劫一場，遍
地橫屍，殘不忍賭。
LONG );
  set("exits",([
     "north" : __DIR__"baistep1",
      "south" : __DIR__"baihutang",
  ]));
  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}