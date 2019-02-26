inherit ROOM;

void create()
{
        set("short", "王府井大街");
        set("long", @LONG
這裏就是京城最為著名的王府井大街。你走在這條繁忙的街道上，
街道上車水馬龍，人來人往，熱鬧非凡。南邊是京城的交通要道東長
安街。可以望見西邊有一座富麗堂皇的建築，那是當朝皇上的第一寵
臣——韋公爺的府邸。東邊就是京城的刑場，是朝廷處決欽犯的場所。
LONG );
       set("exits", ([
                "north" : "/d/beijing/wang_4",
                "south" : "/d/beijing/caroad_e2",
                "east" : "/d/beijing/xingchang",
                "west" : "/d/beijing/wang_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/shusheng1" : 1,
        ]));

	set("coor/x", -2770);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}