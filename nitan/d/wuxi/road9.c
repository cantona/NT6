// Room: /d/wuxi/road9.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "鄉間小道");
        set("long", @LONG
小道突然變得開闊了許多，兩邊的樹也變得稀少了，可以直接看到
一望無際的田野。前面空出了一個很大的場子，原來，你已經來到了吳
民們敬仰的聖廟泰伯廟的門口了。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "east"   : __DIR__"road8",
                "west"   : __DIR__"taibomiao",
        ]));
        set("objects", ([
                "/d/village/npc/dog" : 1,
        ]));
        set("coor/x", 1020);
	set("coor/y", -790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}