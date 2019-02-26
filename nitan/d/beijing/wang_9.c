inherit ROOM;

void create()
{
        set("short", "王府井大街");
        set("long", @LONG
這裏就是京城最為著名的王府井大街。你走在這條繁忙的街道上，
街道上車水馬龍，人來人往，熱鬧非凡。南邊接京城的交通要道東長
安街，西邊是繁華的地安門東大街廣場。北方穿過地東大街可以到達
文廟。
LONG );
       set("exits", ([
                "north" : "/d/beijing/dong_3",
                "south" : "/d/beijing/wang_7",
                "east" : "/d/beijing/wang_10",
                "west" : "/d/beijing/di_donggc",
        ]));

        set("objects", ([
                "/d/beijing/npc/haoke1" : 1,
        ]));

	set("coor/x", -2780);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}