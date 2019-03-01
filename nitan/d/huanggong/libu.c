// libu.c 吏部

inherit ROOM;

void create()
{
        set("short", "吏部公署");
        set("long", @LONG
這裡是六部之首--吏部官員候朝的朝房.
LONG
        );
        set("exits", ([
                "south" : __DIR__"youmen",
        ]));
        set("objects", ([
                __DIR__"npc/suoetu" : 1,
        ]));
	set("coor/x", -2790);
	set("coor/y", 7701);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}