inherit ROOM;

void create()
{
        set("short", "林間大道");
        set("long", @LONG
這裡是一條林間大道，在樹叢中蜿蜒。這裡已是湖北境內。南邊
是便湖南。
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "north"  : __DIR__"hsroad8",
                "south"  : __DIR__"hsroad6",
        ]));
        set("objects", ([
                "/clone/quarry/gou" : 1,
        ]));

	set("coor/x", -6930);
	set("coor/y", -5680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}