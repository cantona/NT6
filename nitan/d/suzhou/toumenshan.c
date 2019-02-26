// Room: /d/suzhou/toumenshan.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "頭門山");
        set("long", @LONG
頭山門在虎丘山的南面，形似虎頭。隔河照牆上書着“海湧流輝”
四個大字，以示虎丘與大海的淵源關係。
LONG );
        set("outdoors", "suzhou");
//        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"huqiu",
                "west"  : __DIR__"wanjing",
        ]));
        set("objects", ([
                "/d/taishan/npc/jian-ke" : 1,
        ]));
	set("coor/x", 1100);
	set("coor/y", -1030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}