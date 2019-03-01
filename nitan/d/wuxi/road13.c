// Room: /d/wuxi/road13.c
// Winder 2000/02/22 

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "湖邊小徑");
        set("long", @LONG
這是太湖邊上的一條小徑，蜿蜒北去。一路前行，花草漸深。東
面是一望無際的太湖，碧波萬頃，煙波浩渺，眺之身心舒暢。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "southwest"   : __DIR__"road12",
        ]));
        set("coor/x", 1060);
	set("coor/y", -800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}