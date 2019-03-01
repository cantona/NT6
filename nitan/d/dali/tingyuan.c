//Room: /d/dali/tingyuan.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","庭院");
        set("long",@LONG
這裡是鎮南王府的庭院，中間一個小水潭，邊上種著許多不知名
的花，幾只喜鵲在花叢中蹦來跳去，花叢邊有片小竹林，竹影下放著
石桌石凳，經常有人在這下棋。
LONG);
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "west"  : __DIR__"shijing",
            "east"  : __DIR__"chahua1",
            "north" : __DIR__"changlang",
            "south" : __DIR__"shirenfang",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19101);
	set("coor/y", -6861);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}