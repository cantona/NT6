inherit ROOM;

void create()
{
        set("short", "林間道");
        set("long", @LONG
這裏是一條林間小道，在樹叢中蜿蜒。嶺南山林茂密，多產毒蟲，
所以路人經過此地都是非常的小心。
LONG );
        set("objects", ([
                "/clone/beast/dushe": 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "southwest" : __DIR__"road3",
                "southeast" : __DIR__"road5",
        ]));
	set("coor/x", -6640);
	set("coor/y", -9740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}