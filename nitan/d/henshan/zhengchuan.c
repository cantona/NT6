inherit ROOM;

void create()
{
        set("short", "正川門");
        set("long", @LONG
正川門是南岳大廟的第三進。院內則是玄德宗殿，關聖殿，觀音
閣等樓宇。
LONG );
        set("exits", ([ 
               "south"  : __DIR__"kuixingge",
               "north"  : __DIR__"yubeiting",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6890);
	set("coor/y", -5670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}