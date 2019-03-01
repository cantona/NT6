inherit ROOM;

void create()
{
        set("short", "望星樓二層");
        set("long", @LONG
這裡是雅座，文人學士經常在這裡吟詩作畫，富商土豪也在這裡邊吃
喝邊作交易。這裡也是城裡舉辦喜宴的最佳場所。你站在樓上眺望，只覺
得心曠神怡。東面是一池湖水，碧波盪漾，北面則是崇山峻嶺，氣勢雄渾，
巍峨壯觀。
LONG);

        set("no_clean_up", 0);
        set("exits", ([
                  "up" : __DIR__"zuixianlou3",
                  "down" : __DIR__"zuixianlou",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/shike" : 2,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2190);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}