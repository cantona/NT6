inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在一山路上，四周有一座座小山丘。遠處可以看見終年積雪
的山尖。周圍的樹草已經很難看得到了。
LONG );
        set("exits", ([
                "north" : __DIR__"nroad7",
                "south" : __DIR__"nroad5",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "xuedao");
        setup();
        replace_program(ROOM);
}
