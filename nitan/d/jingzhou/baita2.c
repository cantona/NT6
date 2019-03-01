inherit ROOM;

void create()
{
        set("short", "白塔三樓");
        set("long", @LONG
這裡是報恩塔三樓，由于這裡地勢高，一陣微風吹來，說不出的
涼爽，荊州城的風光也盡收眼底。
LONG );
        set("exits", ([  
                  "down" : __DIR__"baita1",
        ]));
        set("objects", ([
                "/d/beijing/npc/shiren" : 1,
        ]));
        set("no_clean_up", 0);

        set("coor/x", -7090);
	set("coor/y", -2040);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}