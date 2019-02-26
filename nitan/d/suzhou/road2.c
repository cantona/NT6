// Room: /d/suzhou/road2.c
// Date: May 31, 98  Java

inherit BUILD_ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在一條青石大道上，人來人往非常繁忙，不時地有人騎着馬匆
匆而過。大道兩旁有一些小貨攤，似乎是一處集市。往東面就是號稱天
堂的蘇州城了。雖然是城外，但是景色宜人，絕對是一個好住處。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west"  : __DIR__"road3",
                "east"  : __DIR__"ximen",
        ]));
	set("coor/x", 1070);
	set("coor/y", -1060);
	set("coor/z", 0);
	setup();
}
