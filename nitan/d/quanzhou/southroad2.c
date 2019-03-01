// Room: /d/quanzhou/southroad2.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "刺桐南路");
        set("long", @LONG
這是泉州的主要幹道，筆直寬廣，車水馬龍，熱鬧非凡。由此東行
便到承天寺，西邊是民宅，西南則是一處阿拉伯宅區。泉州出名的源和
堂便在西邊。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([ 
                "east"      : __DIR__"chengtiansi",
                "west"      : __DIR__"zhaiqu3",
                "north"     : __DIR__"southroad1",
                "southeast" : __DIR__"alabo",
        ]));
	set("coor/x", -900);
	set("coor/y", -7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}