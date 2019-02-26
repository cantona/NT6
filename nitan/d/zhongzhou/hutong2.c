inherit ROOM;

void create()
{
        set("short", "小衚衕");
        set("long", @LONG
這裏是一條小衚衕，就在白天這裏也是昏暗不堪。這裏似
乎到了衚衕的盡頭，有一扇門緊關着。
LONG);
        set("outdoors", "zhongzhou");
        set("exits", ([
                "north"     : __DIR__"liwu",
                "southwest" : __DIR__"hutong1",
        ]));
        set("objects", ([
                __DIR__"npc/dipi" : 1,
        ]));

        set("coor/x", -9010);
	set("coor/y", -1000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}