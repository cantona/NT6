inherit ROOM;

void create()
{
        set("short", "王府井大街");
        set("long", @LONG
這裡就是京城最為著名的王府井大街。你走在這條繁忙的街道上，
街道上車水馬龍，人來人往，熱鬧非凡。南邊是京城的交通要道東長
安街，東邊鄰街處有一家當舖。
LONG );
       set("exits", ([
                "north" : "/d/beijing/wang_8",
                "south" : "/d/beijing/wang_4",
                "west" : "/d/beijing/wang_5",
                "east" : "/d/beijing/dangpu",
        ]));

        set("objects", ([
                "/d/beijing/npc/boy2" : 1,
        ]));

	set("coor/x", -2770);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}