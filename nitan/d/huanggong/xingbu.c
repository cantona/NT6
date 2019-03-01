// Room: /d/huanggong/xingbu.c

inherit ROOM;

void create()
{
        set("short", "刑部公署");
        set("long", @LONG
這裡是六部之五--刑部官員候朝的朝房.
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"zuomen",
        ]));
	set("coor/x", -2820);
	set("coor/y", 7691);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}