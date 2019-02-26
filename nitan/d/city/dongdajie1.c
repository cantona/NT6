// Room: /city/dongdajie1.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "東大街");
        set("long", @LONG
這是一條寬闊的青石板街道，向東西兩頭延伸。東邊不時地傳來
金屬撞擊聲，西邊人聲嘈雜。北邊是一座簡樸的院子，半月形的大門
上方寫着『白鹿書院』四個燙金大字，蒼勁有力。裏面不時地傳來學
生們抑揚頓挫的讀書聲。南邊是一家雜貨鋪。
LONG );
        set("outdoors", "city");
	set("exits", ([
		"east" : "/d/city/dongdajie2",
		"south" : "/d/city/zahuopu",
		"west" : "/d/city/guangchang",
		"north" : "/d/city/shuyuan",
	]));

	set("objects", ([
		"/clone/npc/xunbu" : 1,
	]));
	set("coor/x", 10);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}