inherit ROOM;

void create()
{
        set("short", "東大街");
        set("long", @LONG
東大街是開封府內東街區的主要通道。道路的兩端店舖府第不斷。
行人如縷，觀光的，作生意的，攀交情的，以至走親訪友的，南邊不
遠就是山陝甘會館。西面是開封鐵塔。東面則是名滿天下的紅花會的
總舵所在。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"eroad2",
                  "west" : __DIR__"tieta",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5030);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}