//Room: /d/dali/sheguta.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","蛇骨塔");
        set("long", @LONG
蛇骨塔位于大理城內，建在點蒼山斜陽峰東坡。相傳洱海有妖蛇
名『薄劫』，其尾塞海口，洪水泛濫，有勇士段赤城只身入洱海與妖
蛇同歸于盡。後人建塔以震水勢，用蛇骨灰塔，水勢自息。這是一座
密椽式方形磚塔。
LONG );
        set("objects", ([
           "/d/dali/npc/kid": 1,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "east"  : "/d/dali/taihejiekou",
            "west"  : "/d/dali/qingchi",
        ]));
	set("coor/x", -19140);
	set("coor/y", -6880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}