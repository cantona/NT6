//room: chengdedian.c
inherit ROOM;

void create()
{
  set("short","成德殿");
        set("long", @LONG
這就是日月神教教主平日發號施令的地方，殿中無窗，殿口點着
明晃晃的蠟燭，大殿彼端高設一座，坐着一個英俊的中年人，自是名
震江湖的東方不敗的姘頭楊蓮亭了！ 
LONG );

  set("valid_startroom", 1);
  set("exits",([
      "north" : __DIR__"huoting",
      "westdown":__DIR__"up4",
  ]));
  set("objects",([
      __DIR__"npc/dizi" : 2,
      __DIR__"npc/yang"    :1,
        //CLASS_D("riyue") + "/first" : 1,
  ]));
//  set("no_clean_up", 0); 
  setup();
  replace_program(ROOM);
  "/clone/board/riyue_b"->foo();
}
