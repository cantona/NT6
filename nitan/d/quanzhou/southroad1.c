// Room: /d/quanzhou/southroad1.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "刺桐南路");
        set("long", @LONG
這是泉州的主要幹道，筆直寬廣，車水馬龍，熱鬧非凡。刺桐南路
的東邊是打錫巷，西邊有一大片民宅，四通八達，連着武館和戲院。北
邊便是熱鬧的中心廣場。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([ 
                "east"  : __DIR__"daxixiang",
                "west"  : __DIR__"zhaiqu1",
                "north" : __DIR__"guangchang",
                "south" : __DIR__"southroad2",
        ]));
	set("coor/x", -900);
	set("coor/y", -7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}