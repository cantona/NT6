inherit ROOM;

void create()
{
        set("short",  "南大街" );
        set("long", @LONG
你走在昆明最繁華的街道上，人來人往，好不熱鬧，西邊
有一家客店，人們大多選擇這裏落腳，以便在趕路。東邊聽裏
面傳來的談笑聲看，肯定是一家茶鋪。
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "south" : __DIR__"nanmen", 
                "north" : __DIR__"nandajie1",
                "west"  : __DIR__"kedian",
                "east"  : __DIR__"chapu",
        ]));
        set("objects", ([
                "/d/beijing/npc/girl2" : 1,
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -16840);
	set("coor/y", -7230);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}