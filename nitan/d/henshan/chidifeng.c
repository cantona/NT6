inherit ROOM;

void create()
{
        set("short", "赤帝峰");
        set("long", @LONG
相傳祝融能以火施化，是黃帝的火正官，並主管南方的事務，死
後葬于此，故名赤帝峰。
LONG );
        set("exits", ([
                "southdown"  : __DIR__"shanlu2",
                "eastdown"   : __DIR__"shanlu11",
                "northdown"  : __DIR__"shanlu3",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6900);
	set("coor/y", -5580);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}