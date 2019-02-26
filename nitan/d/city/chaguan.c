// Room: /city/chaguan.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "春來茶館");
        set("long", @LONG
你一走進來，就聞到一股茶香沁入心脾，精神為之一爽。幾張八
仙桌一字排開，坐滿了客人，或高聲談笑，或交頭接耳。你要想打聽
江湖掌故和謠言，這裏是個好所在。
LONG );
	set("resource/water", 1);
	set("exits", ([
		"east" : "/d/city/nandajie2",
//                "up" : "/d/city/chashi",
	]));
	set("objects", ([
		"/d/city/npc/aqingsao" : 1,
	]));
	set("coor/x", -10);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
        "/clone/board/player_b"->foo();
}