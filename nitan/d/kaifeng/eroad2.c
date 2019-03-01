inherit ROOM;

void create()
{
        set("short", "東大街");
        set("long", @LONG
東大街是開封府內東街區的主要通道。道路的兩端店舖府第不斷。
行人如縷，觀光的，作生意的，攀交情的，以至走親訪友的。東面就
是山陝甘會館。西面有梯道可上角樓。
LONG );
        set("objects", ([
                  __DIR__"npc/qigai" : 1,
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"eroad1",
                  "north" : __DIR__"eroad3",
                  "east" : __DIR__"huiguan",
                  "westup" : __DIR__"jiaolou2",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5030);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}