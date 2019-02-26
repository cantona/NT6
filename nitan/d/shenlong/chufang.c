// Room: chufang.c

inherit ROOM;

void create()
{
	set("short", "廚房");
	set("long", @LONG
這是神龍島的廚房，中央擺着大圓桌，周圍則放着幾張竹椅。神
龍島的弟子都在這裏用餐。
LONG );
	set("exits",([
	    "west" :__DIR__"zoulang",
	]));
	set("objects",([
		"/clone/food/jitui" : 3,
		"/clone/food/jiudai" : 1,
        ]));

	set("resource/water", 1);
        set("no_fight", 1);
        setup();
	replace_program(ROOM);
}
