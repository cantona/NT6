inherit ROOM;

void create()
{
        set("short", "林間道");
        set("long", @LONG
這裏是一條林間小道，在樹叢中蜿蜒。嶺南山林茂密，多產毒蟲，
所以路人經過此地都是非常的小心。
LONG );
        set("objects", ([
                __DIR__"obj/shuzhi": 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "northeast" : __DIR__"road14",
                "southwest" : __DIR__"road11",
        ]));
	set("coor/x", -6490);
	set("coor/y", -9730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}