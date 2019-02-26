inherit ROOM;

void create()
{
        set("short", "望星樓三層");
        set("long", @LONG
這裏是雅座，文人學士經常在這裏吟詩作畫，富商土豪也在這裏邊吃
喝邊作交易。這裏也是城裏舉辦喜宴的最佳場所。你站在樓上眺望，只覺
得心曠神怡。東面是一池湖水，碧波盪漾，北面則是崇山峻嶺，氣勢雄渾，
巍峨壯觀。
LONG);

        set("no_clean_up", 0);
        set("exits", ([
                  "up" : __DIR__"zuixianlou4",
                  "down" : __DIR__"zuixianlou2",
        ]));
        set("objects", ([
                "/d/zhongzhou/npc/fushang" : 2,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2190);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}