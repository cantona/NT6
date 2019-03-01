// Room: /city/zxlpath.c
// YZC 1995/12/04 

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "醉仙樓大堂");
        set("long", @LONG
這是醉仙樓大堂，來來往往的客人和跑堂小二，夾雜着三個宴會
廳刺耳的呼叫聲，碰杯聲，打鬧聲，賴酒聲，熱鬧非凡。你在三個宴
會廳前打量着進哪個湊個熱鬧，蹭點白食。    東邊是玫瑰廳，朝南
的是牡丹廳，向北是芙蓉廳。
LONG );
	set("exits", ([
		"east"   : "/d/city/meigui",
		"north"  : "/d/city/furong",
		"south"  : "/d/city/mudan",
		"west"   : "/d/city/zuixianlou2",
	]));
        set("no_fight","1");
	set("no_clean_up", 0);
	set("coor/x", 20);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
