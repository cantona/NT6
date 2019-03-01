// Room: /city/neizain.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "內宅");
        set("long", @LONG
這裡是衙門的內宅，住著知府的家眷。外人到此就該止步了。
LONG );
	set("exits", ([
		"south" : "/d/city/ymzhengting",
	]));
	set("objects", ([
		"/d/city/npc/yuhuan" : 1,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -10);
	set("coor/y", 30);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}