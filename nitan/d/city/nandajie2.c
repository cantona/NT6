// Room: /city/nandajie2.c
// YZC 1995/12/04 
// CLEANSWORD 1996/2/2

inherit ROOM;

void create()
{
	set("short", "南大街");
        set("long", @LONG
你走在一條繁華的街道上，向南北兩頭延伸。南邊是南城門，北
邊通往市中心，西邊是一家顧客眾多的茶館，三教九流人士都在那裏
談天説地。東邊的揚州有名的喝花酒的地方——麗春院。麗春院白天
門可羅雀，但是到了晚上卻是熱鬧非凡。隱約可以聽見那兩層的樓房
內傳來陣陣女子的浪笑聲，讓你心頭一蕩。
LONG );
        set("outdoors", "city");
	set("exits", ([
		"east"  : "/d/city/lichunyuan",
		"south" : "/d/city/nanmen",
		"west"  : "/d/city/chaguan",
		"north" : "/d/city/nandajie1",
	]));
        set("objects", ([
                CLASS_D("shaolin") + "/tuoboseng" : 1,
        ]));
	set("coor/x", 0);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
}