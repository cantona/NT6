//room: 
inherit ROOM;
void create()
{
  set("short","長廊");
        set("long", @LONG
這裡是白虎堂的長廊。兩邊一片狼籍，看樣子剛被洗劫一場，遍
地橫屍，殘不忍睹。
LONG );
  set("exits",([
      "east" : __DIR__"dating2",
      "south" : __DIR__"baistep2",
  ]));
  set("objects",([
     __DIR__"npc/jiaotu"   :1,
  ]));
//  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}