inherit ROOM;

void create()
{
        set("short", "御碑亭");
        set("long", @LONG
御碑為重修南嶽廟大石碑，高數丈，石碑豎立在重三萬八千斤的
大石龜上，龜身雕刻細膩，極為生動。
LONG );
        set("exits", ([ 
               "south"  : __DIR__"zhengchuan",
               "north"  : __DIR__"jiayingmen",
        ]));

        set("no_clean_up", 0);

	set("coor/x", -6890);
	set("coor/y", -5660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}