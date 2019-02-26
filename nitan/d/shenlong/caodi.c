#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "草地");
    set("long", @LONG
這裏是一片青青的草地，有幾個少年在玩耍。四周開滿了各色的
鮮花，一陣涼風吹過，清新的空氣中傳來幾縷淡淡的花香。
LONG );

	set("exits", ([
		"south" : __DIR__"kongdi",
		"north" : __DIR__"xiaowu",
	]));
	set("outdoors", "shenlong");
	setup();
	replace_program(ROOM);
}
