//Room: /d/dali/zhengdian.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","正殿");
        set("long", @LONG
這裡是大理國皇宮的正殿，大理皇帝通常都在這裡處理國事，但
現在皇帝不在，所以顯得不那麼拘謹，往南是長廊。
LONG );
        set("exits",([ /* sizeof() == 1 */
            "south"  : "/d/dali/hualang",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19140);
	set("coor/y", -6820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}