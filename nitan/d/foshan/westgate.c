inherit ROOM;

void create()
{
        set("short", "西門");
        set("long", @LONG
這裏乃是佛山鎮的西門。嶺南以西經由廣西可至大理。東面一條
東西向的大街是佛山鎮的主要街道。
LONG );
        set("outdoors", "foshan");
        set("exits", ([
                "east" : __DIR__"street1",
                "west" : __DIR__"road7",
        ]));
	set("coor/x", -6600);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}