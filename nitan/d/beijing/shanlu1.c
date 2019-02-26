inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這裏是荒涼的山路，只有一條蜿蜒崎嶇的小徑。
LONG );
        set("exits", ([
                "northup" : "/d/beijing/shanlu2",
                "eastdown": "/d/beijing/zhuang1",
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7620);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}