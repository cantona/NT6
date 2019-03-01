inherit ROOM;

void create()
{
        set("short","北門");
        set("long", @LONG
這裡是佛山鎮的北門。出北門再向北，翻過南嶺可達中原。南面
一條東西向的大街是佛山鎮的主要街道。
LONG );
        set("outdoors", "foshan");
        set("exits", ([
                "south" : __DIR__"street3",
                "north" : __DIR__"nanling",
        ]));
	set("coor/x", -6570);
	set("coor/y", -9740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}