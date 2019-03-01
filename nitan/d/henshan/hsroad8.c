inherit ROOM;

void create()
{
        set("short", "林間道");
        set("long", @LONG
這裡是一條林間小道，在樹叢中蜿蜒。西北方連著一條黃土路，
南面的道路要寬一些。
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "northwest" : "/d/yueyang/nanmen",
                "south"     : __DIR__"hsroad7",
        ]));

	set("coor/x", -6930);
	set("coor/y", -5670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}