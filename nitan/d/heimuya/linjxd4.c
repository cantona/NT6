// ROOM : linjxd4.c
inherit ROOM;
void create()
{
  set("short","林間小道");
        set("long", @LONG
你走在一條陰暗的林間小道上，兩旁是陰森森的樹林。一陣陣風
吹過樹梢，發出沙沙的響聲，令你不寒而栗。
LONG );
  set("exits",([
      "south" : __DIR__"linjxd6",
      "north" : __DIR__"linjxd1",     
      "east"  : __DIR__"linjxd2",
      "west"  : __DIR__"linjxd5",
  ]));
        set("objects", ([
            CLASS_D("riyue") + "/renwoxing": 1,

        ]));

  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}