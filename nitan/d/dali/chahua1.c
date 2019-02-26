//Room: /d/dali/chahua1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","茶花園門");
        set("long", @LONG
大理茶花冠絕天下，鎮南王府的茶花自然更非凡品。你站在茶花
園口，對着滿園春色，不禁大喜過望。東邊就進園了，北邊是一個庫
房。南邊是一棟廂房，那裏是休息的地方。
LONG );
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/bingqiku",
            "south"  : "/d/dali/xiuxishi",
            "east"   : "/d/dali/chahua2",
            "west"   : "/d/dali/tingyuan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19091);
	set("coor/y", -6861);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}