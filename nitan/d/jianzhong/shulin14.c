//Room: songlin2.c 松林 
//Date: Sep 22 1997

inherit ROOM;

void create()
{
      set("short","樹林");
      set("long",@LONG
這是樹林深處，暗無天日，朦朧中只感覺到左右前後到處
都是樹影。
LONG);
      set("outdoors", "jianzhong");
      set("exits",([ /* sizeof() == 1 */
          "north"  : __DIR__"shulin14",
          "east"   : __DIR__"shulin13",
          "west"   : __DIR__"shulin2",
          "south"  : __DIR__"shulin3", 
      ]));
        set("coor/x", -400);
        set("coor/y", -470);
        set("coor/z", 0);
        setup();
      replace_program(ROOM);
}