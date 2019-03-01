// Room: /d/wuxi/songhe2.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "鬆鶴樓二樓");
        set("long", @LONG
這裡是雅座，文人學士經常在這裡吟詩作畫，富商土豪也在這裡邊
吃喝邊作交易。這裡也是城裡舉辦喜宴的最佳場所。你站在樓上臨街眺
望，可看見南長街上熱鬧的場景。東面是小河彎彎，連綿而過。向北可
以隱約看到兵營的帳蓬。牆上掛著價格牌子(paizi)。靠窗的一張桌前，
一位青衣書生面前放了幾大碗的水酒，卻是不飲。
LONG );
        set("item_desc", ([
                "paizi" : "本店出售醬排骨及上等花雕酒。\n",
        ]));
        set("exits", ([
                "down"    : __DIR__"songhe",
        ]));
        set("objects", ([
                        __DIR__"npc/jin" : 1,
        ]));
        set("coor/x", 1050);
	set("coor/y", -740);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}