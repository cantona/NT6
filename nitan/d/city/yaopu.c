// Room: /city/yaopu.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "藥鋪");
        set("long", @LONG
這是一家藥鋪，一股濃濃的藥味讓你幾欲窒息，那是從藥櫃上的
幾百個小抽屜裏散發出來的。神醫平一指坐在茶几旁，獨自喝着茶，
看也不看你一眼。一名小夥計站在櫃枱後招呼着顧客。櫃枱上貼着一
張發黃的廣告(guanggao)。
LONG );
	set("item_desc", ([
		"guanggao" : "本店出售以下藥品：
雄黃：\t十兩白銀
其他神藥與老闆面議。\n",
	]));
	set("objects", ([
		"/d/city/npc/ping" : 1,
		"/d/city/npc/huoji" : 1,
	]));
        set("no_fight", 1);    
        set("no_sleep_room", 1);
	set("exits", ([
                 "up" : "/d/city/chanfang",
		"south" : "/d/city/dongdajie2",
	]));
	set("coor/x", 20);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}