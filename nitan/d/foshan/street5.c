inherit ROOM;

void create()
{
        set("short", "東鎮街");
        set("long", @LONG
佛山鎮街東西相連。東邊是鎮東門，南面一堵高牆，牆後便是鳳
天南開的「英雄典當」，非常惹人注目。
LONG );
        set("objects", ([
                "/clone/quarry/gou2" : 1,
                __DIR__"npc/jiading" : 2,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "south" : __DIR__"dangpu",
                "west"  : __DIR__"street4",
                "east"  : __DIR__"eastgate",
        ]));
	set("coor/x", -6550);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}