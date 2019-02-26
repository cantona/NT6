inherit ROOM;

void create()
{
        set("short", "松樹林");
        set("long", @LONG
這裏是一片松樹林，連綿無盡，看不到盡頭。四周都是參天的古
鬆，但許多都莫名其妙的枯死了，只剩下一些樹幹矗立在那裏。陽光
透過枯死的樹枝間隙照射到林中，暖洋洋的。四周是死一般寂靜，你
不由一陣緊張。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "east" : __DIR__"sl8",
                "northwest" : __DIR__"sl4",
                "west" : __DIR__"sl6",
                "northeast" : __DIR__"sl5",
                "north" : __DIR__"caodi",
        ]));

        setup();
        replace_program(ROOM);
}