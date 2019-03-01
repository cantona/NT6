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
        set("exits", ([ /* sizeof() == 8 */
                "southwest" : __DIR__"boshulin7",
                "south" : __DIR__"boshulin7",
                "east" : __DIR__"boshulin7",
                "southeast" : __DIR__"boshulin7",
                "west" : __DIR__"boshulin6",
                "northwest" : __DIR__"boshulin8",
                "north" : __DIR__"boshulin7",
                "northeast" : __DIR__"boshulin7",
        ]));

        set("coor/x", -10630);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
