inherit ROOM;

void create()
{
        set("short", "嘉應門");
        set("long", @LONG
這裏是地方官迎接京師御史官來祭南嶽的地方，是南嶽大廟第五
進門了。門上雕塑也較精細些，懸彩燈籠時時換新。
LONG );
        set("exits", ([ 
               "south"  : __DIR__"yubeiting",
               "north"  : __DIR__"yushulou",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6890);
	set("coor/y", -5650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}