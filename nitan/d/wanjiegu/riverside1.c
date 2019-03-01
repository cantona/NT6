inherit ROOM;

void create()
{
        set("short", "江邊小路");
        set("long", @LONG
這是瀾滄江邊的一條小路，江水滔滔從下面奔騰而過，江面上不
時傳來艄公的號子聲，與江風的呼嘯聲形成一曲動人的交響樂，令人
精神為之一振。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([
                "northup" : __DIR__"riverside2",
        ]));
        set("objects", ([
                "/d/wanjiegu/npc/duck" : 2,
        ]));
        setup();
        replace_program(ROOM);
}