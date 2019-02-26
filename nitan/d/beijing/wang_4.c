inherit ROOM;

void create()
{
        set("short", "王府井大街");
        set("long", @LONG
這裏就是京城最為著名的王府井大街。你走在這條繁忙的街道上，
街道上車水馬龍，人來人往，熱鬧非凡。南邊是京城的交通要道東長
安街。東邊是一個寬闊的校場，從那裏傳來一陣陣士兵操練的聲音。
東邊是朝陽道，通朝陽門，出了朝陽門就是北京城的西郊了。
LONG );
       set("exits", ([
                "north" : "/d/beijing/wang_6",
                "south" : "/d/beijing/wang_2",
                "east" : "/d/beijing/chaoyang_dao1",
                "west" : "/d/beijing/wang_3",
        ]));

	set("coor/x", -2770);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}