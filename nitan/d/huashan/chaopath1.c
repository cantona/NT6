inherit ROOM;

void create()
{
      set("short","朝陽峯小路");
        set("long", @LONG
這裏是朝陽峯小路，山勢陡峭，兩邊下臨深谷，一不小心都會掉
了下去。
LONG );
      set("outdoors", "huashan");
      set("no_clean_up", 0);
      set("exits",([ /* sizeof() == 1 */
          "northeast": __DIR__"chaopath2",
          "southeast": __DIR__"square",
      ]));
      setup();
      replace_program(ROOM);
}
