inherit ROOM;

void create()
{
        set("short", "王府井大街");
        set("long", @LONG
這裏就是京城最為著名的王府井大街。你走在這條繁忙的街道上，
街道上車水馬龍，人來人往，熱鬧非凡。南邊接京城的交通要道東長
安街，西邊不遠處是繁華的地安門東大街廣場。北方是京城著名的『
全聚德』烤鴨店。東邊是一家戲院，是京城百姓休息和娛樂的場所。
LONG );
       set("exits", ([
                "north" : "/d/beijing/quanjude",
                "south" : "/d/beijing/wang_8",
                "west" : "/d/beijing/wang_9",
                "east" : "/d/beijing/xiyuan",
        ]));

        set("objects", ([
                "/d/beijing/npc/youren" : 1,
        ]));

	set("coor/x", -2770);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}