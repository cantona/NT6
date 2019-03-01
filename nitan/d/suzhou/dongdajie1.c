// Room: /d/suzhou/dongdajie1.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "東大街");
        set("long", @LONG
你走在東大街上，踩著堅實的青石板地面。東邊是東大街的延伸，
南面是蘇州城裡一個老字號的當舖，北面是一條小胡同。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"dongdajie2",
                "north"     : __DIR__"hutong1",
                "south"     : __DIR__"dangpu",
                "southwest" : __DIR__"baodaiqiao",
                "northwest" : __DIR__"canlangting",
        ]));
        set("objects", ([
                __DIR__"npc/kid" : 1,
        ]));
	set("coor/x", 1120);
	set("coor/y", -1060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}