inherit ROOM;

void create()
{
      set("short", "華藏庵東廊");
        set("long", @LONG
這裡是峨嵋華藏庵東廊。走廊往南通往齋堂，北通往廣場。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "south" : __DIR__"hcazhaitang", 
          "north" : __DIR__"hcaeast1", 
      ]));
      set("no_clean_up", 0);
      setup();
      replace_program(ROOM);
}