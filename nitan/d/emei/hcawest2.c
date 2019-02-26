inherit ROOM;

void create()
{
      set("short", "華藏庵西廊");
        set("long", @LONG
這裏是峨嵋華藏庵西廊。走廊往南禪房，北邊通往廣場。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "south" : __DIR__"hcachanfang",
          "north" : __DIR__"hcawest1", 
      ]));
      set("no_clean_up", 0);
      setup();
      replace_program(ROOM);
}