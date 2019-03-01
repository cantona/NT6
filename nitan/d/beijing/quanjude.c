inherit ROOM;

void create()
{
        set("short", "全聚德酒樓");
        set("long", @LONG
這裡就是京城中最為著名的全聚德酒樓。方圓數百裡內提起全聚
德酒樓的烤鴨可以說是無人不知，無人不曉。樓內玲瓏八角，紅木舖
地，雕欄玉砌，飛檐上還掛著幾個大紅燈籠，裝潢很是幽雅華麗。店
小二抄著一口流利的京腔熱情的招呼著客人。酒樓西牆邊有一個樓梯，
通往全聚德酒樓二樓的雅座。
LONG );
        set("exits", ([
                "south" : "/d/beijing/wang_10",
                "up"   : "/d/beijing/quanjudeup",
        ]));
        set("objects", ([
                "/d/beijing/npc/xiaoer1" : 1,
        ]));

	set("coor/x", -2770);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}