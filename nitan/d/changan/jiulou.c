//Room: jiulou.c

inherit ROOM;

void create()
{
        set("short", "望星樓");
        set("long", @LONG
望星樓飛檐碧瓦，酒幌高挑，是個二層樓。樓上設有迴廊，雕樑
畫柱，華麗鋪排。下面是青磚牆皮，洞開的小窗繪成紅框，十分素雅。
樓上正中，掛着一塊黑漆漆的橫匾，上面的三個繡金大字『望星樓』
是以狂草書成，筆力雄勁，靈動欲飛。
LONG );
        set("exits", ([
                "south" : "/d/changan/qixiang1",
                "up" : "/d/changan/jiulou2",
        ]));
        set("objects", ([
                "/d/changan/npc/xiaoer2" : 1,
        ]));

        set("coor/x", -10750);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}