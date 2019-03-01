// Room: /city/xidajie1.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "西大街");
        set("long", @LONG
這是一條寬闊的青石板街道，向東西兩頭延伸。西大街是衙門所
在，行人稀少，靜悄悄地很是冷清。東邊是一個熱鬧的廣場。南邊是
兵營。北邊就是衙門了。
LONG );
        set("outdoors", "city");
	set("no_clean_up", 0);
	set("exits", ([
		"east"  : "/d/city/guangchang",
		"south" : "/d/city/bingyindamen",
		"west"  : "/d/city/xidajie2",
		"north" : "/d/city/yamen",
	]));

	set("coor/x", -10);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}