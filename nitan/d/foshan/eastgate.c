inherit ROOM;

void create()
{
        set("short", "東門");
        set("long", @LONG
這裏是佛山鎮的東門。再往東走，不久就要離開佛山去往福建了。
西面一條東西向的大街是佛山鎮的主要街道。
LONG );
        set("outdoors", "foshan");
        set("exits", ([
            "east" : __DIR__"road8",
            "west" : __DIR__"street5",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -6540);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}