inherit ROOM;

void create()
{
        set("short", "素齋廚");
        set("long", @LONG
素齋廚的幾個大灶燒得正旺，白色的蒸汽在室頂舖了一層灶膛間
擺滿了鬆柴，和尚們很挑剔，說是用這種柴禾煮出的飯菜才去近佛。
一邊的桌上擺著一個飯桶。東面有個小門出去。
LONG );
        set("objects", ([
                  __DIR__"npc/suzhai.c" : 1,
                  __DIR__"npc/shaohuo" : 1,
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"chufang",
                  "east" : __DIR__"zoulang",
        ]));

	set("coor/x", -5030);
	set("coor/y", 2210);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}