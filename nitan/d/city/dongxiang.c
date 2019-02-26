// Room: /city/dongxiang.c
// YZC 1995/12/04 

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "財主東廂");
        set("long", @LONG
這是一個昏暗的房間，窗户都被釘死。地上放着皮鞭、木棍等刑
具，顯然這是財主私立公堂，折磨僕人、丫鬟的所在。一個丫鬟被繩
子綁着，渾身赤裸跪在地上哭哭啼啼，身上是一道道的傷口。
LONG );
	set("exits", ([
		"west" : "/d/city/houyuan",
	]));
	set("objects", ([
		"/d/city/npc/hongniang" : 1,
	]));
//	set("no_clean_up", 0);
        set("coor/x", -35);
	set("coor/y", 30);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
