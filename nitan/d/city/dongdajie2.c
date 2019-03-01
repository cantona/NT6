// Room: /city/dongdajie2.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "東大街");
        set("long", @LONG
你走在東大街上，踩著堅實的青石板地面。東邊是東城門，可以
聽到守城官兵的吆喝聲，與西邊朗朗的讀書聲混雜在一起。北邊是一
家老字號的藥舖，南邊是打鐵舖，叮叮當當的聲音老遠就能聽到。
LONG );
        set("outdoors", "city");
	set("exits", ([
		"east"  : "/d/city/dongdajie3",
		"south" : "/d/city/datiepu",
		"west"  : "/d/city/dongdajie1",
		"north" : "/d/city/yaopu",
	]));

	set("coor/x", 20);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}