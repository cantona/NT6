inherit ROOM;

void create()
{
        set("short", "丫鬟卧房");
        set("long", @LONG
這是丫鬟的房間。房中陳設簡單，沒什麼東西。
LONG );

        set("exits", ([
                "east" : __DIR__"houyuan",
        ]));
        set("objects", ([
                __DIR__"npc/juyou" : 1,
        ]));
        set("cost", 0);
        set("coor/x", -7120);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}