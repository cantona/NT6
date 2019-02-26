// Room: /city/dayuan.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "財主大院");
        set("long", @LONG
你走進大院，迎面是一個假山水池，池上擺着一塊奇形怪狀的石
頭，據説是當年花石綱的遺石。水池的兩旁種滿了花草。東邊是一棵
槐樹，鬱鬱葱葱，遮蓋了大半個院子，顯得陰森恐怖。一條長廊走道
通往後院，有幾個家丁貉守。
LONG );
	set("exits", ([
		"north" : "/d/city/houyuan",
		"south" : "/d/city/caizhu",
	]));
	set("objects", ([
		"/d/city/npc/guanjia" : 1,
		"/d/city/npc/jiading" : 2,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -20);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}