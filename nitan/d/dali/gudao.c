//Room: /d/dali/gudao.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","古道");
        set("long",@LONG
一條石板古道，兩邊樹木蒼翠，山勢平緩，南面是一望無際的西
雙版納大森林。大道北面有一片宏偉建築，一堵裏許長的紅牆隔開，
越過牆頭可見一座高樓聳立，正是大理名勝五華樓。
LONG);
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "enter"   : __DIR__"dating",
            "west"    : __DIR__"shanlu6",
            "east"    : __DIR__"luyuxi",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19150);
	set("coor/y", -6920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}