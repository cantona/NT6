inherit ROOM;

void create()
{
      set("short","密林");
        set("long", @LONG
這是黑森森的一片密林，楠木參天，濃陰蔽日。這裏西上是報國
寺，東邊林間隱藏着一座廟宇。
LONG );
      set("exits", ([
          "eastdown"  : __DIR__"fhs",
          "westup"    : __DIR__"jietuopo",
      ]));
      set("outdoors", "emei");
      set("no_clean_up", 0);
        set("coor/x", -390);
        set("coor/y", -230);
        set("coor/z", 20);
        setup();
      replace_program(ROOM);
}