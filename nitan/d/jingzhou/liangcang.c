inherit ROOM;

void create()
{
        set("short", "糧倉");
        set("long", @LONG
這裏就是荊州糧倉了，地上堆着許多麻袋，大概裝的是包穀大米
之類的糧食。
LONG );
        set("exits", ([
                "west" : __DIR__"lcmen",
        ]));

        set("coor/x", -7080);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}