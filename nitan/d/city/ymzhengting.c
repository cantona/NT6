// Room: /city/ymdongting.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "衙門正廳");
        set("long", @LONG
堂上東西有兩根楹住，掛着一幅對聯，但是你無心細看。正牆上
懸掛一個橫匾，上書『正大光明』四個金光閃閃的大字。知府正坐在
文案後批閲文書，師爺隨侍在後。
LONG );
	set("exits", ([
		"east"  : "/d/city/dongting",
		"west"  : "/d/city/xiting",
		"north" : "/d/city/neizhai",
		"south" : "/d/city/yamen",
	]));
	set("objects", ([
		"/d/city/npc/cheng" : 1,
		"/d/city/npc/shiye" : 1,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -10);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}