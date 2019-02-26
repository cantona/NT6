inherit ROOM;

void create()
{
        set("short", "王府井大街");
        set("long", @LONG
這裏就是京城最為著名的王府井大街。你走在這條繁忙的街道上，
街道上車水馬龍，人來人往，熱鬧非凡。南邊是京城的交通要道東長
安街。向北可以地安門東大街。
LONG );
       set("exits", ([
                "north" : "/d/beijing/wang_7",
                "south" : "/d/beijing/wang_3",
                "east" : "/d/beijing/wang_6",
        ]));

	set("coor/x", -2780);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}