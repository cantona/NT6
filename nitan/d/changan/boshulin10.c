// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
        set("short", "柏樹林");
        set("long", @LONG
你眼前豁然開朗，終於走出了這片柏樹林，在往東走是一片雜草
叢生的草地。
LONG
        );
        set("outdoors", "changan");
        set("exits", ([ /* sizeof() == 3 */
                "south" : __DIR__"boshulin9",
                "east" : __DIR__"caodi",
        ]));

        set("coor/x", -10630);
	set("coor/y", 1980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

