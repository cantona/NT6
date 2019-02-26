inherit ROOM;

void create()
{
        set("short", "後殿");
        set("long", @LONG
這裏是關帝廟的後殿，殿中堆放着香、燭等雜物。牆上的幔布看
起來滿新的。
LONG );
        set("exits", ([
                "north" : __DIR__"houmen",
                "south" : __DIR__"guanmiao",
        ]));

        set("coor/x", -7120);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}