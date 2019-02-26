inherit ROOM;

void create()
{
      set("short", "華藏庵西廊");
        set("long", @LONG
這裏是峨嵋華藏庵西廊。走廊往南通往禪房，東通往廣場。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "south" : __DIR__"hcawest2",
          "east"  : __DIR__"hcaguangchang", 
      ]));
      set("coor/x", -570);
        set("coor/y", -330);
        set("coor/z", 220);
        setup();
      replace_program(ROOM);
}