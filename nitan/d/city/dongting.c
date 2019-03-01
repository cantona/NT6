// Room: /city/dongting.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "東廳");
        set("long", @LONG
這裡是衙門東廳，是知府招待客人的所在。廳中擺著一張杉木圓
桌和幾張椅子，桌上是一套精致的宜興瓷器。牆上掛著一幅中堂，畫
的是猛虎下山，乃是知府的手筆。
LONG );
	set("exits", ([
		"west" : "/d/city/ymzhengting",
	]));
	set("no_clean_up", 0);
	set("coor/x", 0);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}