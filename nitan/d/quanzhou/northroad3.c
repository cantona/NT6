// Room: /d/quanzhou/northroad3.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "刺桐北路");
        set("long", @LONG
這是泉州的主要幹道，筆直寬廣，車水馬龍，熱鬧非凡。東邊是都
督巷，可通往都督府。一隊隊的士兵穿來插去，把守森嚴。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"duduxiang",
                "south" : __DIR__"northroad2",
                "north" : __DIR__"weiyuanlou",
        ]));
	set("coor/x", -900);
	set("coor/y", -7640);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}