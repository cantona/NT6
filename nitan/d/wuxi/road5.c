// Room: /d/wuxi/road5.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "大驛道");
        set("long", @LONG
這是官府為駐軍來往與江陰要塞和錫城而專修的一條官道，因為
除要塞外不通向什麼地方，官道上的行人稀少。向南去是北門大橋，
可以遠遠地看見蓮蓉門的城樓。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "south"  : __DIR__"lianrongqiao",
                "north"  : __DIR__"road6",
        ]));
        set("coor/x", 1040);
	set("coor/y", -670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}