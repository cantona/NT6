//Room: /d/dali/xiaojing.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","山區小徑");
        set("long", @LONG
這是清源山區的碎石小徑，曲折蜿蜒，兩旁林木茂盛，遮天蔽日。
滿徑落葉，柔軟稀鬆。蟲鳥啾啾。涼風習習。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "east"    : "/d/dali/jinzhihe",
            "westup"  : "/d/dali/dadieshui",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19100);
	set("coor/y", -6870);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}