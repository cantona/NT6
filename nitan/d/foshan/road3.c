inherit ROOM;

void create()
{
        set("short", "林間道");
        set("long", @LONG
這裏是一條林間小道，在樹叢中蜿蜒。嶺南山林茂密，多產毒蟲，
所以路人經過此地都是非常的小心。
LONG );
        set("outdoors", "foshan");
        set("objects", ([
                "/d/foshan/npc/bee": 1,
        ]));
        set("exits", ([
                "west"      : __DIR__"road2",
                "northeast" : __DIR__"road4",
        ]));
	set("coor/x", -6650);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}