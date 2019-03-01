inherit ROOM;

void create()
{
        set("short", "胡同口");
        set("long", @LONG
往裡走就是洛陽城內老百姓的居住區。只見胡同口兩邊是有些小店面，
有米行、小雜貨舖等。一些居民從這裡進進出出。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"eroad5",
                  "north" : __DIR__"hutong2",
        ]));

	set("coor/x", -6940);
	set("coor/y", 2160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}