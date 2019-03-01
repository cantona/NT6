inherit ROOM;

void create()
{
        set("short", "王府井大街");
        set("long", @LONG
這裡就是京城最為著名的王府井大街。你走在這條繁忙的街道上，
街道上車水馬龍，人來人往，熱鬧非凡。南邊接京城的交通要道東長
安街，西邊通往地安門東大街。從東邊傳來一陣嘈雜的喧鬧聲，那是
京城著名的怡紅院。
LONG );
       set("exits", ([
                "north" : "/d/beijing/wang_10",
                "south" : "/d/beijing/wang_6",
                "east" : "/d/beijing/yihongyuan",
                "west" : "/d/beijing/wang_7",
        ]));

        set("objects", ([
                "/d/beijing/npc/richman1" : 1,
        ]));

	set("coor/x", -2770);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}