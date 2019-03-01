// Room: /t/wanjiegu/riverside2.c

inherit ROOM;

void create()
{
        set("short", "江邊小路");
        set("long", @LONG
這是瀾滄江邊的一條小路，江水滔滔，從下面奔騰而過，江面上
不時傳來艄公的號子聲，與江風的呼嘯聲形成一曲動人的交響樂。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([ /* sizeof() == 3 */
                "southeast" : "/d/dali/road3",
                "southdown" : __DIR__"riverside1",
                "northdown" : __DIR__"riverside3",
        ]));

        setup();
        replace_program(ROOM);
}