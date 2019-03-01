inherit ROOM;

void create()
{
        set("short", "糧倉");
        set("long", @LONG
這裡就是荊州糧倉了，地上堆著許多麻袋，大概裝的是包谷大米
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