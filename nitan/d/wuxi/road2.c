// Room: /d/wuxi/road2.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "東驛道");
        set("long", @LONG
這是蘇州和無錫之間的大驛道，這兩座江南名城相隔得是如此之
近。使得不少做生意的商販都早晚往返于兩城之間也不覺得麻煩。因
路上的人也就特別得多。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"road3",
                "west"  : __DIR__"road1",
        ]));
        set("coor/x", 1090);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}