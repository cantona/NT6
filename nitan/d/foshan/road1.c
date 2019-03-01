inherit ROOM;

void create()
{
        set("short", "小道");
        set("long", @LONG
這裡是一條林間小道，在樹叢中蜿蜒。這裡向東行進可到達廣西。
向西北走就是大理國的地界了。
LONG );
        set("objects", ([
                __DIR__"obj/shikuai": 1,
        ]));

        set("outdoors", "foshan");
        set("exits", ([
	    "southwest" : "/d/dali/road5",
                "east"      : __DIR__"road2",
        ]));
	set("coor/x", -6670);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}