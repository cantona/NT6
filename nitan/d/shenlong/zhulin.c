#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "竹林");
        set("long", @LONG
這裡是一片青竹林，一陣涼風吹過，竹葉沙沙作響。東邊是神龍
教的大廳，西邊則是教主的居室。
LONG );

        set("exits", ([
	        "east" : __DIR__"dating",
	        "west" : __DIR__"jushi",
        ]));
        set("outdoors", "shenlong");
        setup();
        replace_program(ROOM);
}
