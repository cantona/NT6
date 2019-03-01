//Room: /d/dali/zhulou1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","竹樓下");
        set("long",@LONG
台夷人喜居竹林深處，房舍自然少不了用竹子搭成，竹為樑，竹
為牆，竹樓建的相當精緻。下層基本上只是四根柱子架空的，既可以
作獸圈，也為了防蛇。一架竹梯通向上層的房舍。
LONG);
        set("objects", ([
           __DIR__"npc/cow": 1,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "south"   : __DIR__"wuding",
            "up"      : __DIR__"zhulou2",
        ]));
	set("coor/x", -19150);
	set("coor/y", -6960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}