// Room: /d/suzhou/dongdajie2.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "東大街");
        set("long", @LONG
你走在東大街上，踩著堅實的青石板地面。東邊是東城門，可以聽
到守城官兵的吆喝聲，北邊是一家老字號的藥舖，南邊是打鐵舖，叮叮
當當的聲音老遠就能聽到。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"dongmen",
                "north"     : __DIR__"yaopu",
                "south"     : __DIR__"datiepu",
                "west"      : __DIR__"dongdajie1",
                "northwest" : __DIR__"hutong3",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
	set("coor/x", 1130);
	set("coor/y", -1060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}