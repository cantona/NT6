//Room: /d/dali/luwang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","魯望鎮");
        set("long",@LONG
這裡是普麼部的魯望鎮，普麼部屬台夷，領屬還有附近的越州。
這是一座建在山坡上的小鎮，東面和北面是高聳的群山，向西和南眺
望均可見村莊和城鎮。
LONG);
        set("objects", ([
           __DIR__"npc/tshangfan": 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "west"    : __DIR__"feilihu",
            "east"    : __DIR__"yulin",
            "south"   : __DIR__"shuitian",
            "north"   : __DIR__"zhulou3",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}