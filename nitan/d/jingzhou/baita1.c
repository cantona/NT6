inherit ROOM;

void create()
{
        set("short", "白塔二樓");
        set("long", @LONG
這裏是報恩塔的第二樓，相傳是前朝一位狀元郎考取功名後，衞
報答母恩修建的報恩塔。由於這裏地勢高，讓人忍不住要登高眺望。
LONG );
        set("exits", ([  
                  "up" : __DIR__"baita2",
                  "down" : __DIR__"baita",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -7090);
	set("coor/y", -2040);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}