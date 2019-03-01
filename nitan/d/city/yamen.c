// Room: /city/yamen.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "衙門大門");
        set("long", @LONG
這裡是衙門大門，兩扇朱木大門緊緊關閉著。『肅靜』『回避』
的牌子分放兩頭石獅子的旁邊。前面有一個大鼓，顯然是供小民鳴冤
用的。幾名衙役在門前巡邏。
LONG );
	set("exits", ([
		"south" : "/d/city/xidajie1",
		"north" : "/d/city/ymzhengting",
	]));
	set("objects", ([
		"/d/city/npc/yayi" : 4,
	]));
	set("coor/x", -10);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
	if (!wizardp(me) && objectp(present("ya yi", environment(me))) && dir == "north")
		return notify_fail("衙役喝道：“威……武……。”\n");
	return ::valid_leave(me, dir);
}