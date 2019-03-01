//Room: yunupath2.c 玉女峰山路
//Date: Oct. 2 1997 by Venus
inherit ROOM;

void create()
{
      set("short","玉女峰山路");
        set("long", @LONG
這裡是玉女峰後山的一條山路。路邊長滿了翠竹，每當微風拂過，
竹葉便沙沙作響，顯得分外的幽靜。
LONG );
      set("outdoors", "huashan");
      set("no_clean_up", 0);
      set("exits",([ /* sizeof() == 1 */
          "southup"   : __DIR__"siguoya",
          "northdown" : __DIR__"yunupath1",
      ]));
      setup();
      replace_program(ROOM);
}