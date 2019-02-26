inherit ROOM;

void create()
{
        set("short", "北帝廟");
        set("long", @LONG
北帝廟坐北朝南。院子中一個大水塘，塘中石龜石蛇，昂然盤踞。
大殿神像石板上血跡殷然。北帝神像立於大殿的正中。
LONG );
        set("exits", ([
                "south"  : __DIR__"street1",
        ]));
	set("coor/x", -6590);
	set("coor/y", -9740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}