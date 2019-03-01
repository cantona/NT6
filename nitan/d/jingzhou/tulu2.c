//Edited by fandog, 02/18/2000

inherit ROOM;
void create()
{
        set("short", "黃土路");
        set("long", @LONG
這是一條黃土路，不時可見江湖中人背著包袱，別著刀劍往北走去。
地上有許多馬車碾過的痕跡。
LONG );
        set("exits", ([
                "north"      : __DIR__"tulu1",
                "west"       : __DIR__"tulu3",
                "southeast"  : "/d/yueyang/beimen",
                "southwest"  : "/d/kunming/yunnan1",
        ]));
        set("outdoors", "jingzhou");
        set("no_clean_up", 0);
        set("coor/x", -7100);
	set("coor/y", -2170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}