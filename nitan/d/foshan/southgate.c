inherit ROOM;

void create()
{
        set("short", "南門");
        set("long", @LONG
這裏是佛山鎮的南門。從出南門再向南行進，就到達南海之濱了。
北面一條東西向的大街是佛山鎮的主要街道。
LONG );
        set("outdoors", "foshan");
        set("exits", ([
                "north" : __DIR__"street3",
                "south" : "/d/xiakedao/xkroad3",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -6570);
	set("coor/y", -9760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}