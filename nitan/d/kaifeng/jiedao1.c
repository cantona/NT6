inherit ROOM;

void create()
{
        set("short", "御街");
        set("long", @LONG
這條道橫貫南北，北到宣德門，南至南盈門，是以前皇上出巡時
常走的道，所以修得是格外平整。道兩邊店舖不斷。西面就是開封府
的大堂，再向南一點就可以出城了。
LONG );
        set("outdoors", "kaifeng");
        set("exits", ([
                  "west" : __DIR__"kaifeng",
                  "north" : __DIR__"jiedao",
                  "south" : __DIR__"jiedao2",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -5040);
	set("coor/y", 2150);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}