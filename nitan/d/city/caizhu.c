// Room: /city/caizhu.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "財主大門");
        set("long", @LONG
一座富麗堂皇的大宅院出現在你的眼前，兩頭高大的石獅子鎮守
在了大門兩側，朱漆大門足足有三寸厚。門上掛着兩個燈籠，寫着『
崔』字。崔家是當地首富，而且以蠻橫著稱。幾條狼狗嚎叫着向你衝
了過來。
LONG );
	set("exits", ([
		"south" : "/d/city/xidajie2",
		"north" : "/d/city/dayuan",
	]));
	set("objects", ([
		"/d/city/npc/wolfdog" : 2,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -20);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}