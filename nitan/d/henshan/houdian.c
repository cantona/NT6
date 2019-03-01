inherit ROOM;

void create()
{
        set("short", "後殿");
        set("long", @LONG
後殿是南岳大廟的第八進，也是南岳大帝的寢宮。
LONG );
        set("exits", ([
               "south"  : __DIR__"dadian",
               "north"  : __DIR__"beimen",
        ]));

        set("no_clean_up", 0);

	set("coor/x", -6890);
	set("coor/y", -5620);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}