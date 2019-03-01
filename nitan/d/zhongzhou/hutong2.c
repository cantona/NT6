inherit ROOM;

void create()
{
        set("short", "小胡同");
        set("long", @LONG
這裡是一條小胡同，就在白天這裡也是昏暗不堪。這裡似
乎到了胡同的盡頭，有一扇門緊關著。
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