//Room: songlin2.c 松林 
//Date: Sep 22 1997

inherit ROOM;

void create()
{
      set("short","山谷");
      set("long",@LONG
順着小溪，你不知不覺中來到了一個幽靜的山谷，
綠樹成蔭，山花燦爛。只是北方隱隱傳來幾聲雄
壯悲嗆的雕鳴，打破了四周的寂靜。
LONG);
      set("outdoors", "jianzhong");
      set("exits",([ /* sizeof() == 1 */
          "west"  : __DIR__"shulin14",
          "east"   : __DIR__"shulin14",
          "north"   : __DIR__"shangu",
          "south"  : __DIR__"shulin3", 
      ]));
        set("coor/x", -400);
        set("coor/y", -470);
        set("coor/z", 0);
        setup();
      replace_program(ROOM);
}