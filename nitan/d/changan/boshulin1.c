// This program is a part of NT MudLIB

inherit ROOM;
void create()
{
        set("short", "柏樹林");
        set("long",@LONG
這裏是一片枝繁葉茂的柏樹林，花草長得便地都是，看着這原始
的密林，你似乎迷失了方向。
LONG
        );
        set("outdoors", "changan");
        set("exits", ([
                "northeast" :__DIR__"boshulin2",
                "southeast" :__DIR__"boshulin1",
                "east" :__DIR__"boshulin1",
                "north" :__DIR__"boshulin1",
                "west" :__DIR__"boshulin1",
                "northwest" :__DIR__"boshulin1",
                "southwest" :__DIR__"boshulin1",
                "south" :__DIR__"road4",
        ]));
        set("coor/x", -10650);
	set("coor/y", 1940);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

