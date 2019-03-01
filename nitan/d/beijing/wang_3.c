inherit ROOM;

void create()
{
        set("short", "王府井大街");
        set("long", @LONG
這裡就是京城最為著名的王府井大街。你走在這條繁忙的街道上，
街道上車水馬龍，人來人往，熱鬧非凡。南邊是京城的交通要道東長
安街。東邊是一個寬闊的校場，從那裡傳來一陣陣士兵操練的聲音。
東邊是朝陽道，通朝陽門，出了朝陽門就是北京城的西郊了。
LONG );
       set("exits", ([
                "north" : "/d/beijing/wang_5",
                "south" : "/d/beijing/wang_1",
                "east" : "/d/beijing/wang_4",
                "west" : "/d/beijing/xiaochang",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing1" : 1,
        ]));

	set("coor/x", -2780);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}