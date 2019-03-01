//Room: xiaopath1.c 小山路
//Date: Oct. 2 1997 by Venus
inherit ROOM;

void create()
{
      set("short","小山路");
        set("long", @LONG
這裡是華山的一條小山路，地勢較為平緩，不似其它地方那麼險
峻。你走在這裡，四周靜悄悄的，你就象走進了一個世外桃源。
LONG );
      set("outdoors", "huashan");
      set("exits",([ /* sizeof() == 1 */
          "southwest"     : __DIR__"yunu",
          "northeast"     : __DIR__"xiaolu2",
      ]));
      set("no_clean_up", 0);
      setup();
      replace_program(ROOM);
}