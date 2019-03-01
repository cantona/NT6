//Room: /d/dali/shuangheqiao.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","雙鶴橋");
        set("long", @LONG
這是一個岔路口，北邊是座青石拱橋名叫雙鶴橋，此橋跨在綠玉
溪上，橋北即是大理城，由此南去是通往南方的喜州、龍口等城鎮的
官道，東去的岔路通往廣西，沿綠玉溪南岸西行可達五華樓。
LONG );
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "north"     : "/d/dali/southgate",
            "west"      : "/d/dali/luyuxi",
            "south"     : "/d/dali/road4",
            "southeast" : "/d/dali/road5",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19130);
	set("coor/y", -6920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}