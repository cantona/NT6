// ROOM : linjxd5.c
inherit ROOM;
void create()
{
  set("short","林間小道");
        set("long", @LONG
你走在一條陰暗的林間小道上，兩旁是陰森森的樹林。一陣陣風
吹過樹梢，發出沙沙的響聲，令你不寒而慄。忽然你發現樹叢中有兩
點綠芒，一閃即沒！！
LONG );
  set("exits",([
      "southup" : __DIR__"dating1",
      "north" : __DIR__"linjxd4",     
      "east"  : __DIR__"linjxd3",
      "west"  : __DIR__"linjxd5",
  ]));
  set("objects",([
      __DIR__"npc/wolf" : 4 ,
  ]));
//  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}