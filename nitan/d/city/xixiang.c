// Room: /city/xixiang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "財主西廂");
        set("long", @LONG
這是財主小姐的閨房，一股幽香撲面而來。一張繡榻放在牆角，
垂著細紗。小姐正躺在榻上，懶洋洋地一幅思春模樣。看到你突然闖
進來，驚呆了。
LONG );
	set("exits", ([
		"east" : "/d/city/houyuan",
	]));
	set("objects", ([
		"/d/city/npc/yingying" : 1,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -30);
	set("coor/y", 30);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}