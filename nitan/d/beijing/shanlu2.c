inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這裏是荒涼的山路，只有一條蜿蜒崎嶇的小徑，這裏荒無人煙，
讓人覺得背後冷颼颼的。
LONG );
        set("exits", ([
                "westup"    : "/d/beijing/shanlu3",
                "southdown" : "/d/beijing/shanlu1",
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7630);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}