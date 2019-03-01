// Room: /city/xidajie2.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "西大街");
        set("long", @LONG
你走在西大街上，感到這裡的街面要比別處的幹凈、整潔。大概
因為靠近衙門、兵營可受保護的緣故，富人們都喜歡住在這裡。東邊
靜悄悄地沒有幾個行人，西邊是西城門通往郊外。南邊是一座武館，
北邊是一所富麗堂皇的大宅院。
LONG );
        set("outdoors", "city");
	set("no_clean_up", 0);
	set("exits", ([
		"east"  : "/d/city/xidajie1",
		"south" : "/d/city/wuguan",
		"west"  : "/d/city/xidajie3",
		"north" : "/d/city/caizhu",
	]));

        set("objects", ([
                "/d/quanzhen/npc/youfang": 1,
	]));

	set("coor/x", -20);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}