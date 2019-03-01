// Room: /d/suzhou/wanjing.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "萬景山莊");
        set("long", @LONG
在虎丘山東面就是萬景山莊，是一個較大的盆景園，有盆名為“秦
漢遺韻”的圓柏，樹齡已逾五百年，被譽為“盆景之王”。還有盆景為
“雲蒸霞蔚”的樹石盆景和另一盆四百多年的雀梅古樁盆景，都是盆景
藝術的中的珍品。圓內景色優美，頗富園林雅趣。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "eastup" : __DIR__"shijianshi",
                "east"   : __DIR__"toumenshan",
                "westup" : __DIR__"hanhanquan",
        ]));
        set("objects", ([
                "/d/taishan/npc/dao-ke" : 1,
        ]));
	set("coor/x", 1090);
	set("coor/y", -1030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}