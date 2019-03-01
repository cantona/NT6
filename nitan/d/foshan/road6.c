inherit ROOM;

void create()
{
        set("short", "林間道");
        set("long", @LONG
這裡是一條林間小道，在樹叢中蜿蜒。嶺南山林茂密，多產毒蟲，
所以路人經過此地都是非常的小心。
LONG );
        set("objects", ([
                __DIR__"obj/shikuai": 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "west" : __DIR__"road5",
                "east" : __DIR__"road7",
        ]));
        set("objects", ([
                __DIR__"npc/youming" :  1,
        ]));
	set("coor/x", -6620);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}