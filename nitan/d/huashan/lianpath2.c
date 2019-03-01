//Roon: lianpath1.c 蓮花峰小路
//Date: Oct. 2 1997 by Venus
inherit ROOM;

void create()
{
      set("short","蓮花峰小路");
        set("long", @LONG
小路通往蓮花峰，周圍靜靜悄悄，微聞蟬鳴。四望密林幽谷，讓
人膽寒。
LONG );
      set("outdoors", "huashan");
      set("no_clean_up", 0);
      set("exits",([ /* sizeof() == 1 */
          "westup"   : __DIR__"chengxiang",
          "eastdown" : __DIR__"lianpath1",
      ]));
      setup();
      replace_program(ROOM);
}
