// This program is a part of NT MudLIB

inherit ROOM;
void create()
{
        set("short", "柏樹林");
        set("long", @LONG
這裡是一片枝繁葉茂的柏樹林，花草長得便地都是，看著這原始
的密林，你似乎迷失了方向。
LONG
);
        set("outdoors", "changan");
        set("exits", ([
                "northeast" :__DIR__"boshulin2",
                "southeast" :__DIR__"boshulin2",
                "east" :__DIR__"boshulin2",
                "north" :__DIR__"boshulin3",
                "south" :__DIR__"boshulin2",
                "northwest" :__DIR__"boshulin2",
                "southwest" :__DIR__"boshulin1",
                "west" :__DIR__"boshulin2",
        ]));
        set("coor/x", -10640);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

