inherit ROOM;

void create()
{
        set("short", "全聚德酒樓二樓");
        set("long", @LONG
這裏是雅座，文人學士經常在這裏吟詩作畫，富商土豪也在這裏
邊吃喝邊作交易。這裏也是城裏舉辦喜宴的最佳場所。這裏出售天下
聞名的全聚德烤鴨。你站在樓上眺望京城，只覺得心曠神怡。
LONG );
        set("exits", ([
                "down"   : "/d/beijing/quanjude",
        ]));
        set("objects", ([
                "/d/beijing/npc/cheng" : 1,
        ]));

	set("coor/x", -2770);
	set("coor/y", 7730);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}