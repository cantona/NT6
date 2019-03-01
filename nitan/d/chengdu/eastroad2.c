// Room: eastroad2.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "東大街");
        set("long", @LONG
你走在東大街上，踩着堅實的青石板地面。東邊是東城門，可以
聽到守城官兵的吆喝聲。西邊是蜀都大道，那邊一派肅靜。原來是因
為提督府在那頭。南北是一條寬直的大道。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "east"  : __DIR__"eastgate",
            "west"  : __DIR__"shuduroad1",
            "north" : __DIR__"eastroad1",
            "south" : __DIR__"eastroad3",
        ]));
        set("objects", ([
            "/d/city/npc/liumangtou" : 1,
            "/d/city/npc/liumang"    : 2,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15200);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}