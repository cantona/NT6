// Room: /city/bingqiku.c
// YZC 1995/12/04 

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "兵器庫");
        set("long", @LONG
這裏是兵器庫，到處銀光閃閃，讓人眼花繚亂。寶刀、寶劍、金
箍棒，大刀、長劍、哨棒，短刀、短劍、短棍，各色各樣的兵器應有
盡有，你一時不知道挑什麼好。
LONG );
	set("exits", ([
		"north" : "/d/city/bingyin",
	]));
	set("no_clean_up", 0);
	create_door("north", "鐵門", "south", DOOR_CLOSED);
	set("coor/x", -10);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();
}