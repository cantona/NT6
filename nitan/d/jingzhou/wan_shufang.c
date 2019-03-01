// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "書房");
        set ("long", @LONG
這是萬老爺子的書房。擺設簡單整潔。左首一堵白牆特別惹眼。
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "south" : __DIR__"wan_xilou",
        ]));

        set("no_clean_up", 0);
        set("coor/x", -7120);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}