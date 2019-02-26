inherit ROOM;

void create()
{
        set("short", "白塔");
        set("long", @LONG
這裏是一座三層高的白塔，相傳是前朝一位狀元郎考取功名後，
衞報答母恩修建的報恩塔。
LONG );
        set("exits", ([  
                  "up" : __DIR__"baita1",
                  "south" : __DIR__"dongdajie1",
        ]));
        set("no_clean_up", 0);
        set("objects", ([
                "/d/beijing/npc/shusheng2" : 1,
        ]));
        set("coor/x", -7090);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}