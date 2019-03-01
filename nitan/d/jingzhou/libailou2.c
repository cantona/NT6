inherit ROOM;

void create()
{
        set("name", "李白樓");
        set("short", "李白樓二樓");
        set("long", @LONG
這裡是雅座，文人學士經常在這裡吟詩作畫，富商土豪也在這裡
邊吃喝邊作交易。這裡是城裡舉辦喜宴的最佳場所。你站在樓上眺望，
只覺得心曠神怡。東面是一池湖水，碧波盪漾。北面是崇山峻嶺，而
南面可以看到聞名全國的白鹿書院的後庭。牆上掛著價格牌子(paizi
)。
LONG );

        set("item_desc", ([
                "paizi" : "本店出售烤鴨及上等花雕酒。\n",
        ]));


        set("exits", ([
                "down" : __DIR__"libailou",
        ]));

        setup();
        replace_program(ROOM);
}