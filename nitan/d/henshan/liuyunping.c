inherit ROOM;

void create()
{
        set("short", "流雲坪");
        set("long", @LONG
每逢雨霽，在後山深壑中升騰起來的雲山霧海，湧過南天門山脊
向前山傾瀉，直如銀河飛瀉，蔚為壯觀，這就是南天門的流雲奇景。
LONG );
        set("exits", ([ 
               "westdown"  : __DIR__"nantian",
               "eastup"    : __DIR__"shilinfeng",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6930);
	set("coor/y", -5520);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}