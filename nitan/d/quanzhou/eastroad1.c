// Room: /d/quanzhou/eastroad1.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "刺桐東路");
        set("long", @LONG
這是泉州的主要幹道，筆直寬廣，車水馬龍，熱鬧非凡。北邊的糧
倉裏有士兵把守，以防賊盜洗劫。往東可至恩怨巷，再到擂台。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"eastroad2",
                "west"  : __DIR__"guangchang",
                "north" : __DIR__"liangcang",
        ]));
	set("coor/x", -890);
	set("coor/y", -7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}