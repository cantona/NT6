inherit ROOM;

void create()
{
      set("short", "西牆");
        set("long", @LONG
這裏是峨眉山報國寺的西牆。寺院裏的鐘聲從牆那邊飄來，在空
氣中迴響。一條山溪從西面山上的解脱橋下流經這裏，向山下淌去。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "east"      : __DIR__"bgs",
      ]));
      set("no_clean_up", 0);
        set("coor/x", -380);
        set("coor/y", -220);
        set("coor/z", 10);
        setup();
      replace_program(ROOM);
}