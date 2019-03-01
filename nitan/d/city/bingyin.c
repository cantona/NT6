// Room: /city/bingyin.c
// YZC 1995/12/04 

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "兵營");
        set("long", @LONG
這裡是兵營，密密麻麻到處都是官兵，有的在武將的指揮下列隊
操練，有的獨自在練功，有的坐著、躺著正在休息。南牆下坐著主帥，
不動聲色地尋視著四周。看到你進來，他們全都悄悄的向你包圍了過
來，形勢看來不太妙。南邊有一扇門(men)。
LONG );
	set("item_desc", ([
		"men" : "這是一扇極厚的鐵門。\n",
	]));
	set("exits", ([
		"south" : "/d/city/bingqiku",
		"north" : "/d/city/bingyindamen",
	]));
	set("objects", ([
		"/d/city/npc/shi" : 1,
		"/d/city/npc/wujiang" : 2,
		"/d/city/npc/bing" : 2,
	]));
//	set("no_clean_up", 0);
	create_door("south", "鐵門", "north", DOOR_CLOSED);
	set("coor/x", -10);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
}
int valid_leave(object me, string dir)
{
	if (!wizardp(me) && objectp(present("guan bing", environment(me))) && 
		dir == "south")
		return notify_fail("官兵攔住了你的去路。\n");
	return ::valid_leave(me, dir);
}