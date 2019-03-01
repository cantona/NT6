inherit ROOM;

void create()
{
        set("short", "英豪酒家二樓");
        set("long", @LONG
這是英豪酒家二樓雅座，如果靠窗坐的話，街上行人可以
盡收眼底，你如果喜歡清凈一點，就在裡面包間。邊上還有個
單間，喝多了可以上裡面小酣片刻。
LONG);

        set("exits", ([
                "west" : __DIR__"xiuxishi",
                "down" : __DIR__"yinghao",
        ]));
        set("objects", ([
                  __DIR__"npc/richman" : 1,
        ]));

        set("coor/x", -9030);
	set("coor/y", -990);
	set("coor/z", 10);
	setup();
}