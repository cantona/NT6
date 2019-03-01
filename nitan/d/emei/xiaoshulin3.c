inherit ROOM;

void create()
{
      set("short","小樹林");
        set("long", @LONG
這是峨嵋山金頂華藏庵外的一片小樹林。林中沒有路，但地上依
稀有些足跡，似乎剛有人走過。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "southeast" : __DIR__"xiaoshulin4", 
          "north"     : __DIR__"xiaoshulin2", 
      ]));
      set("no_clean_up", 0);
      setup();
      replace_program(ROOM);
}