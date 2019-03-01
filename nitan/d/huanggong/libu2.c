//libu2.c  禮部

inherit ROOM;

void create()
{
        set("short", "禮部公署");
        set("long", @LONG
這裡是六部之三--禮部官員候朝的朝房.
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"youmen",
        ]));
	set("coor/x", -2790);
	set("coor/y", 7681);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}