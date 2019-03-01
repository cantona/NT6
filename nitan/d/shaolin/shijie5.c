// Room: /d/shaolin/shijie5.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
一掛巨大的瀑布白龍出霄般橫越山間，水氣已濃得仿佛可以滴下
水珠兒來。山巒間升起薄弧的青霧，凝聚不散。嘩嘩的水聲震耳欲聾。
石階上滿是水漬，走上去滑得可以讓人打跌。。
LONG );
        set("exits", ([
                "southdown" : __DIR__"shijie4",
                "northup" : __DIR__"shijie6",
        ]));
        set("outdoors", "shaolin");
        setup();
        replace_program(ROOM);
}
