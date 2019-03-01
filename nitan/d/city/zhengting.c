// Room: /city/zhengting.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "正廳");
        set("long", @LONG
這裡是福威鏢局的正廳，幾只太師椅一字排開，正中央坐著總鏢
頭，手持煙袋桿正在閉目沉思。牆上掛著幾幅字畫和一把寶劍。
LONG );
	set("exits", ([
		"north" : __DIR__"biaoju",
	]));
	set("objects", ([
                "/quest/quest1/linzhennan" : 1,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -30);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}