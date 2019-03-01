// jiulou2.c
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "酒樓二樓");
        set("long", @LONG
這裡是雅座，文人學士經常在這裡吟詩作畫，富商土豪也在這裡邊
吃喝邊作交易。這裡也是城裡舉辦喜宴的最佳場所。你站在樓上眺望，
只覺得心懷坦盪。四周全是漫漫的黃沙，比之江南的花香鳥語，氣勢更
是浩盪。酒樓的牆上掛著一塊牌子(paizi)。
LONG
        );
        set("item_desc", ([
                "paizi" : "本店出售烤鴨及上等花雕酒。\n",
        ]));
        set("objects", ([
                __DIR__"npc/zhanggui" : 1,
        ]));

        set("exits", ([
                "down" : __DIR__"jiulou1",
        ]));

        set("coor/x", -12250);
	set("coor/y", 830);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}