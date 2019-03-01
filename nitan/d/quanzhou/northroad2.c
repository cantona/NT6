// Room: /d/quanzhou/northroad2.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "刺桐北路");
        set("long", @LONG
這是泉州的主要幹道，筆直寬廣，車水馬龍，熱鬧非凡。西北方連
著一條巷子，可通往城隍廟。
LONG );
        set("outdoors", "quanzhou");
        set("objects", ([
                "/d/city/npc/liumang" : 1,
        ]));
        set("exits", ([
                "south"     : __DIR__"northroad1",
                "north"     : __DIR__"northroad3",
                "northwest" : __DIR__"chenghuangxiang",
        ]));
	set("coor/x", -900);
	set("coor/y", -7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}