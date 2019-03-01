//Room: /d/dali/zoulang3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","走廊");
        set("long",@LONG
這是一條長長的走廊，通向各個客人的寢室。到了二樓，毛
氈已經換成純白，兩側木壁上或刻有花鳥魚蟲，或掛了些許時人
的字畫，每隔七八步，就有一處香台，縷縷青煙從銅鶴嘴裏游出，
聞之精神一振。
LONG);
        set("exits",([ /* sizeof() == 1 */
            "enter"    : __DIR__"guibingshi1",
            "west"     : __DIR__"zoulang1",
            "east"     : __DIR__"zoulang4",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19141);
	set("coor/y", -6911);
	set("coor/z", 9);
	setup();
        replace_program(ROOM);
}