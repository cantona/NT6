// jiulou1.c
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "酒樓");
        set("long", @LONG
這家酒樓是武功鎮方圓百里內的唯一一家，不過連名字都沒
有。樓下佈置簡易，顧客多是匆匆的行人，買點包子、雞腿、米
酒就趕路去了。樓上是雅座。
LONG
        );
        set("exits", ([
                "south" : __DIR__"beijie",
                "up" : __DIR__"jiulou2",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));

        set("coor/x", -12250);
	set("coor/y", 830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}