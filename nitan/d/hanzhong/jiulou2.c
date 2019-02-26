// jiulou2.c
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "酒樓二樓");
        set("long", @LONG
這裏是雅座，文人學士經常在這裏吟詩作畫，富商土豪也在這裏邊
吃喝邊作交易。這裏也是城裏舉辦喜宴的最佳場所。你站在樓上眺望，
只覺得心懷坦蕩。四周全是漫漫的黃沙，比之江南的花香鳥語，氣勢更
是浩蕩。酒樓的牆上掛着一塊牌子(paizi)。
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