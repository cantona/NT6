// Room: /d/nanyang/jiulou2.c
// Last Modified by winder on Nov. 20 2001

inherit ROOM;

void create()
{
        set("name", "迎賓樓");
        set("short", "迎賓樓二樓");
        set("long", @LONG
這裏是雅座，文人學士經常在這裏吟詩作畫，富商土豪也在這裏
邊吃喝邊作交易。這裏也是城裏舉辦喜宴的最佳場所。你站在樓上眺
望，只覺得心曠神怡。東面是一池湖水，碧波盪漾。北面是崇山峻嶺。
牆上掛着價格牌子(paizi)。
LONG );
        set("item_desc", ([
                "paizi" : "本店專辦上等素齊。\n",
        ]));
        set("exits", ([
                "down" : __DIR__"jiulou1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -6950);
	set("coor/y", 770);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}