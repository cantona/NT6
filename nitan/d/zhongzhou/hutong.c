inherit ROOM;

void create()
{
        set("short", "小衚衕");
        set("long", @LONG
這裏是一條小衚衕，就在白天這裏也是昏暗不堪。
LONG);
        set("outdoors", "zhongzhou");

        set("exits", ([
                "southwest" : __DIR__"wendingnan3",
                "northeast" : __DIR__"hutong1",                  
        ]));

        set("coor/x", -9030);
	set("coor/y", -1020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}