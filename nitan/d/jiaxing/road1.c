// Room: /d/jiaxing/road1.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
這是一條郊外的土路，兩邊生長著蓬亂的茅草。路邊是江南水鄉到
處都可以見到的小河。遠處似乎有座村落。
LONG
        );
        set("no_clean_up", 0);
        set("outdoors","jiaxing");

        set("exits", ([
                "northwest" : __DIR__"road",
                "south"     : __DIR__"road2",
        ]) );

	set("coor/x", 1230);
	set("coor/y", -1800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}