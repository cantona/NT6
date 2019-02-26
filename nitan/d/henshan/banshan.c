inherit ROOM;

void create()
{
        set("short", "半山亭");
        set("long", @LONG
終於到了半山亭。這裏離到祝融峯無論高程還是行程，均恰好是
一半之徑，路邊小亭顯然已極古久，但仍為過往客旅遮風避雨。
LONG );

        set("exits", ([
               "southdown"  : __DIR__"shanlu4",
               "northwest"    : __DIR__"shanlu002",
        ]));

        set("no_clean_up", 0);
        set("outdoors", "henshan");

	set("coor/x", -6910);
	set("coor/y", -5550);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}