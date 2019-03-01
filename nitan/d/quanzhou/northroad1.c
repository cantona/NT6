// Room: /d/quanzhou/northroad1.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "刺桐北路");
        set("long", @LONG
這是泉州的主要幹道，筆直寬闊，車水馬龍，熱鬧非凡。南面是熱
鬧喧嘩的中心廣場，嘈雜的聲音遠遠便能聽到。東邊有家鴻福樓。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([ 
                "east"  : __DIR__"kedian",
                "south" : __DIR__"guangchang",
                "north" : __DIR__"northroad2",
        ]));
	set("coor/x", -900);
	set("coor/y", -7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}