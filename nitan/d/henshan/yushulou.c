inherit ROOM;

void create()
{
        set("short", "御書樓");
        set("long", @LONG
御書樓為南嶽廟歷代藏書之處，天子御賜，賢達樂捐，這裏早已
洋洋大觀。
LONG );
        set("exits", ([
               "south"  : __DIR__"jiayingmen",
               "north"  : __DIR__"dadian",
        ]));

        set("no_clean_up", 0);

	set("coor/x", -6890);
	set("coor/y", -5640);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}