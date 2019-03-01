#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "神龍洞");
    set("long", @LONG
這裡便是當年收伏蛇精的英雄─賽神龍的棲身之地，據說，當年
賽神龍耗盡畢生功力將蛇精鎮壓于蛇洞內，而自己卻終身守護在蛇洞
內，以防蛇精重出人間。
LONG);

	set("exits", ([
		"out" : __DIR__"dong2.16",
		"north": __DIR__"shedong3",
		"south":__DIR__"shedong4",
		"west":__DIR__"shedong2",
		
		
		
	]));
	set("objects",  ([
		__DIR__"npc/sai" : 1,
	]));
		
	setup();
	replace_program(ROOM);
}
