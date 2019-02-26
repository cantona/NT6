inherit ROOM;

void create()
{
        set("short", "王府井大街");
        set("long", @LONG
這裏就是京城最為著名的王府井大街。你走在這條繁忙的街道上，
街道上車水馬龍，人來人往，熱鬧非凡。南邊是京城的交通要道東長
安街。西邊是一座富麗堂皇的建築，那是當朝皇上的第一寵臣——韋
公爺的府邸。東邊不遠是京城的刑場，是朝廷處決欽犯的場所。
LONG );
       set("exits", ([
                "north" : "/d/beijing/wang_3",
                "south" : "/d/beijing/caroad_e1",
                "east" : "/d/beijing/wang_2",
                "west" : "/d/beijing/weifu_men",
        ]));
        set("objects", ([
                "/d/beijing/npc/youren" : 1,
        ]));

	set("coor/x", -2780);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}